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
        self.m1 = bullet.btMatrix3x3.identity
        self.m2 = bullet.btMatrix3x3.identity

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
        del self.m1
        del self.m2


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
        # Damping should cap at 1.0
        self.body1.set_damping(20, 20)
        self.assertEquals(self.body1.linear_damping, 1.0)
        self.assertEquals(self.body1.angular_damping, 1.0)

    def test_linear_sleeping_threshold(self):
        self.info.linear_sleeping_threshold = 0.2
        self.body2 = bullet.btRigidBody(self.info)
        self.assertEquals(self.body2.linear_sleeping_threshold,
                          self.info.linear_sleeping_threshold)

    def test_linear_factor(self):
        self.v1.x = 1
        self.body1.linear_factor = self.v1
        self.assertEquals(self.body1.linear_factor, self.v1)
        self.v1.y = 1
        self.assertNotEquals(self.body1.linear_factor, self.v1)

    def test_mass_props(self):
        self.v1 = bullet.btVector3(1, 0, 0)
        self.body1.set_mass_props(10.0, self.v1)
        self.assertEquals(self.body1.inv_mass, 1.0/10.0)

    def test_inertia_tensor(self):
        self.body1.update_inertia_tensor()
        self.m1 = self.body1.get_inv_inertia_tensor_world()
        self.assertEquals(self.m1, self.m2)

    def test_forces(self):
        self.body1.center_of_mass_transform = self.t1
        self.v1.y = 10.0
        self.body1.apply_central_force(self.v1)
        self.v1 = self.body1.get_total_force()
        self.v2 = self.body1.get_total_torque()
        self.assertEquals(self.v2, self.v3)
        self.v3.y = 10.0
        self.assertEquals(self.v1, self.v3)
        self.body1.clear_forces()
        self.v3.y = 0.0
        self.v1 = self.body1.get_total_force()
        self.v2 = self.body1.get_total_torque()
        self.assertEquals(self.v1, self.v3)
        self.assertEquals(self.v2, self.v3)

    def test_apply_force(self):
        self.v1.y = 10.0
        self.v2.y = 20.0
        self.body2.apply_force(self.v1, self.v3)
        self.body2.apply_torque(self.v2)
        self.v1 = self.body2.get_total_force()
        self.v2 = self.body2.get_total_torque()
        self.assertEquals(self.v1, bullet.btVector3(0, 10, 0))
        self.assertEquals(self.v2, bullet.btVector3(0, 20, 0))

    def test_inv_inertia_diag_local(self):
        self.v1.x = 10.0
        self.body1.inv_inertia_diag_local = self.v1
        self.assertEquals(self.body1.inv_inertia_diag_local, self.v1)

    def test_sleeping_thresholds(self):
        lin, ang = 0.1, 0.2
        self.body1.set_sleeping_thresholds(lin, ang)
        self.assertEquals(self.body1.linear_sleeping_threshold, lin)
        self.assertEquals(self.body1.angular_sleeping_threshold, ang)

    def test_impulses(self):
        self.v1.y = 10
        self.v2.y = 20
        self.body1.apply_central_impulse(self.v1)
        self.body1.apply_torque_impulse(self.v2)
        self.body2.apply_impulse(self.v1, self.v3)
        self.assertEquals(self.body1.linear_velocity, self.v1)
        self.assertEquals(self.body1.angular_velocity, self.v2)

    def test_center_of_mass(self):
        self.body1.center_of_mass_transform = self.t1
        self.assertEquals(self.body1.center_of_mass_transform, self.t1)
        self.v2 = self.body1.get_center_of_mass_position()
        self.v3 = self.body1.center_of_mass_position
        print(self.v3)
        self.assertEquals(self.v2, self.v3)

        def _set_position():
            self.body1.center_of_mass_position = self.v1
        self.assertRaises(AttributeError, _set_position)

    def test_velocities(self):
        self.v1.y = 10
        self.body1.linear_velocity = self.v1
        self.assertEquals(self.body1.linear_velocity, self.v1)
        self.v2.y = 20
        self.body1.angular_velocity = self.v2
        self.assertEquals(self.body1.angular_velocity, self.v2)
        self.v3.x = 1
        self.v1 = self.body1.get_linear_velocity_in_local_point(self.v3)
        self.assertEquals(self.v1, self.body1.linear_velocity +
                          self.body1.angular_velocity.cross(self.v3))

    def test_translate(self):
        self.v1.z = 10
        self.body1.translate(self.v1)
        self.assertEquals(self.body1.world_transform.origin, self.v1)

    def test_aabb(self):
        self.body1.get_aabb(self.v1, self.v2)
        self.v3 = bullet.btVector3(1, 1, 1)
        self.assertEquals(self.v1, -self.v3)
        self.assertEquals(self.v2, self.v3)

    def test_broadphase_proxy(self):
        # TODO: Further testing needed when integrated in a world
        self.body1.broadphase_proxy

    def test_motion_state(self):
        state = self.body1.motion_state
        self.body1.motion_state = state
        self.assertIsNotNone(self.body1.motion_state)

    def test_angular_factor(self):
        self.v1.x = 1.0
        self.body1.angular_factor = self.v1
        self.assertEquals(self.body1.angular_factor, self.v1)
        self.body1.set_angular_factor(1.0)
        self.v2 = bullet.btVector3(1, 1, 1)
        self.assertEquals(self.body1.angular_factor, self.v2)

    def test_in_world(self):
        self.assertFalse(self.body1.in_world)

    def test_flags(self):
        self.body1.flags = 1
        self.assertEquals(self.body1.flags, 1)
        self.body1.flags = 0
        self.assertEquals(self.body1.flags, 0)
