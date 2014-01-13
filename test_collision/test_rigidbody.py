#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_rigidbody
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class RigidBodyDataMixin(object):
    def setUp(self):
        self.step = 1.0/60
        self.motion_state1 = bullet.btDefaultMotionState()
        self.motion_state2 = bullet.btDefaultMotionState()
        self.radius = 1.0
        self.inertia = bullet.btVector3(1, 1, 1)
        self.sphere_shape = bullet.btSphereShape(self.radius)
        self.points = [
            bullet.btVector3(-1, -1, -1),
            bullet.btVector3(-1, 1, -1),
            bullet.btVector3(-1, -1, 1),
            bullet.btVector3(-1, 1, 1),
            bullet.btVector3(1, 1, 1),
            bullet.btVector3(1, -1, 1),
            bullet.btVector3(1, -1, -1),
            bullet.btVector3(1, 1, -1)
        ]
        self.hull = bullet.btConvexHullShape(self.points)
        self.info = bullet.btRigidBodyConstructionInfo(
            1.0,
            self.motion_state1,
            self.sphere_shape,
            self.inertia
        )
        self.v1 = bullet.btVector3(0, 0, 0)
        self.v2 = bullet.btVector3(0, 0, 0)
        self.v3 = bullet.btVector3(0, 0, 0)
        self.t1 = bullet.btTransform.identity
        self.t2 = bullet.btTransform.identity
        self.body1 = bullet.btRigidBody(self.info)
        self.body2 = bullet.btRigidBody(1.0, self.motion_state2,
                                        self.hull, self.v1)

    def tearDown(self):
        del self.body1
        del self.info
        del self.t1
        del self.t2
        del self.sphere_shape
        del self.hull
        del self.inertia
        del self.radius
        del self.motion_state1
        del self.motion_state2
        del self.v1
        del self.v2
        del self.v3


class RigidBodyCInfoTestCase(RigidBodyDataMixin,
                             unittest.TestCase):
    def test_ctor(self):
        pass

    def test_motion_state(self):
        self.t2.origin = bullet.btVector3(10, 0, 0)
        self.motion_state1.set_world_transform(self.t2)
        self.info.motion_state.get_world_transform(self.t1)
        self.assertEquals(self.t1, self.t2)

    def test_collision_shape(self):
        self.assertEquals(self.sphere_shape.radius,
                          self.info.collision_shape.radius)
        self.info.collision_shape = self.hull
        self.assertEquals(self.info.collision_shape.num_points,
                          len(self.points))
        self.assertTrue(isinstance(self.info.collision_shape,
                        bullet.btConvexHullShape))

    def test_mass(self):
        self.info.mass = 10.1
        self.assertEquals(self.info.mass, 10.1)

    def test_start_world_transform(self):
        self.t2.origin = bullet.btVector3(10, 0, 0)
        self.t1 = bullet.btTransform(self.t2)
        self.start_world_transform = self.t2
        self.assertEquals(self.t1, self.t2)

    def test_local_inertia(self):
        self.v1 = bullet.btVector3(1, 0, 0)
        self.v2 = bullet.btVector3(self.v1)
        self.info.local_inertia = self.v1
        self.assertEquals(self.info.local_inertia, self.v2)

    def test_local_linear_damping(self):
        self.info.local_linear_damping = 10.1
        self.assertEquals(self.info.local_linear_damping, 10.1)

    def test_local_angular_damping(self):
        self.info.local_angular_damping = 20.12
        self.assertEquals(self.info.local_angular_damping, 20.12)

    def test_friction(self):
        self.info.friction = 123
        self.assertEquals(self.info.friction, 123)

    def test_rolling_friction(self):
        self.info.rolling_friction = 21
        self.assertEquals(self.info.rolling_friction, 21)

    def test_linear_sleeping_threshold(self):
        self.info.linear_sleeping_threshold = 0.2
        self.assertEquals(self.info.linear_sleeping_threshold,
                          0.2)

    def test_angular_sleeping_threshold(self):
        self.info.angular_sleeping_threshold = 0.1
        self.assertEquals(self.info.angular_sleeping_threshold, 0.1)

    def test_additional_damping(self):
        self.assertFalse(self.info.additional_damping)
        self.info.additional_damping = True
        self.info.additional_damping_factor = 1.2
        self.assertTrue(self.info.additional_damping)
        self.assertEquals(self.info.additional_damping_factor, 1.2)

        self.info.additional_linear_damping_threshold_sqr = 2.1
        self.assertEquals(self.info.additional_linear_damping_threshold_sqr,
                          2.1)

        self.info.additional_angular_damping_threshold_sqr = 2.1
        self.assertEquals(self.info.additional_angular_damping_threshold_sqr,
                          2.1)

        self.info.additional_angular_damping_factor = 2.1
        self.assertEquals(self.info.additional_angular_damping_factor,
                          2.1)


class RigidBodyTestCase(RigidBodyDataMixin,
                        unittest.TestCase):

    def test_ctor(self):
        self.body1 = bullet.btRigidBody(self.info)
        self.v1 = bullet.btVector3(1, 0, 0)
        self.body2 = bullet.btRigidBody(1.0, self.motion_state1,
                                        self.hull, self.v1)

    def test_upcast(self):
        """
        Upcast is not really testable as we don't have typecasting
        in python but we'll use a poor man's substitute
        """
        self.body3 = bullet.btRigidBody.upcast(self.body1)
        self.assertIsNotNone(self.body3)
        del self.body3

    def test_predict_integrated_transform(self):
        self.body1.predict_integrated_transform(self.step, self.t1)
        # TODO: implement when velocity is implemented

    def test_save_kinematic_state(self):
        self.body1.save_kinematic_state(self.step)

    def test_apply_gravity(self):
        self.body1.apply_gravity()

    def test_gravity(self):
        self.v1.y = -9.8
        self.body1.gravity = self.v1
        self.assertEquals(self.body1.gravity.y, -9.8)

    def test_damping(self):
        self.body1.set_damping(0.1, 0.2)
        self.assertEquals(self.body1.linear_damping, 0.1)
        self.assertEquals(self.body1.angular_damping, 0.2)
