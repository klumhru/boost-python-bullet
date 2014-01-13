#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_rigidbody
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class RigidBodyCInfoTestCase(unittest.TestCase):
    def setUp(self):
        self.motion_state = bullet.btDefaultMotionState()
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
            self.motion_state,
            self.sphere_shape,
            self.inertia
        )
        self.v1 = bullet.btVector3(0, 0, 0)
        self.v2 = bullet.btVector3(0, 0, 0)
        self.v3 = bullet.btVector3(0, 0, 0)
        self.t1 = bullet.btTransform.identity
        self.t2 = bullet.btTransform.identity

    def test_ctor(self):
        pass

    def test_motion_state(self):
        self.t2.origin = bullet.btVector3(10, 0, 0)
        self.motion_state.set_world_transform(self.t2)
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

    def tearDown(self):
        del self.info
        del self.t1
        del self.t2
        del self.sphere_shape
        del self.hull
        del self.inertia
        del self.radius
        del self.motion_state
        del self.v1
        del self.v2
        del self.v3
