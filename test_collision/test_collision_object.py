#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_collision_object
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class CollisionObjectTestCase(unittest.TestCase):
    def setUp(self):
        self.o1 = bullet.btCollisionObject()
        self.shape = bullet.btSphereShape(1.0)
        self.bp = bullet.btDbvtBroadphase()
        self.v1 = bullet.btVector3(0, 0, 0)
        self.v2 = bullet.btVector3(0, 0, 0)
        self.v3 = bullet.btVector3(0, 0, 0)
        self.t1 = bullet.btTransform.identity
        self.t2 = bullet.btTransform.identity

    def test_ctor(self):
        pass

    def test_anisotropic_friction(self):
        self.assertFalse(self.o1.has_anisotropic_friction())
        self.v1.y = 1.0
        self.o1.set_anisotropic_friction(self.v1)
        self.v2 = self.o1.get_anisotropic_friction()
        self.assertEquals(self.v1, self.v2)
        self.assertTrue(self.o1.has_anisotropic_friction())

    def test_contact_processing_threshold(self):
        self.o1.contact_processing_threshold = 0.2
        f = self.o1.contact_processing_threshold
        f *= 1.1
        self.o1.contact_processing_threshold = f
        self.assertEquals(f, self.o1.contact_processing_threshold)

    def test_dynamic_properties(self):
        self.assertTrue(self.o1.static_object)
        self.assertFalse(self.o1.kinematic_object)
        self.assertTrue(self.o1.static_or_kinematic_object)

    def test_shape(self):
        self.o1.collision_shape = self.shape
        self.assertEquals(self.o1.collision_shape.radius, self.shape.radius)

    def test_activation_state(self):
        self.assertEquals(self.o1.activation_state, 1)
        self.o1.activate(True)
        self.o1.force_activation_state(2)
        self.assertEquals(self.o1.activation_state, 2)

    def test_restitution(self):
        self.o1.restitution = 2.1
        self.assertEquals(self.o1.restitution, 2.1)

    def test_friction(self):
        self.o1.friction = 2.1
        self.assertEquals(self.o1.friction, 2.1)

    def test_rolling_friction(self):
        self.o1.rolling_friction = 2.1
        self.assertEquals(self.o1.rolling_friction, 2.1)

    def test_internal_type(self):
        self.assertEquals(self.o1.internal_type, 1)

    def test_world_transform(self):
        self.assertFalse(self.t1 is self.t2)
        self.o1.world_transform = self.t1
        self.t2 = self.o1.world_transform
        self.assertEquals(self.t1, self.t2)
        self.v1 = bullet.btVector3(0, 0, 10)
        self.o1.world_transform.origin = self.v1
        self.assertEquals(self.o1.world_transform.origin, self.v1)

    def test_interpolation_world_transform(self):
        self.assertFalse(self.t1 is self.t2)
        self.o1.interpolation_world_transform = self.t1
        self.t2 = self.o1.interpolation_world_transform
        self.assertEquals(self.t1, self.t2)
        self.v1 = bullet.btVector3(0, 0, 10)
        self.o1.interpolation_world_transform.origin = self.v1
        self.assertEquals(self.o1.interpolation_world_transform.origin, self.v1)

    def test_interpolation_dynamics(self):
        self.v1 = bullet.btVector3(1, 0, 0)
        self.v2 = bullet.btVector3(0, 1, 0)
        self.o1.interpolation_linear_velocity = self.v1
        self.o1.interpolation_angular_velocity = self.v2
        self.assertEquals(self.o1.interpolation_linear_velocity, self.v1)
        self.assertEquals(self.o1.interpolation_angular_velocity, self.v2)

    def test_island_tag(self):
        self.o1.island_tag = 1
        self.assertEquals(self.o1.island_tag, 1)

    def test_companion_id(self):
        self.o1.companion_id = 1
        self.assertEquals(self.o1.companion_id, 1)

    def test_hit_fraction(self):
        self.o1.hit_fraction = 2.0
        self.assertEquals(self.o1.hit_fraction, 2.0)

    def test_collision_flags(self):
        self.o1.collision_flags = bullet.CollisionFlags.CF_KINEMATIC_OBJECT
        self.assertEquals(self.o1.collision_flags,
                          bullet.CollisionFlags.CF_KINEMATIC_OBJECT)
        self.o1.collision_flags = (bullet.CollisionFlags.CF_KINEMATIC_OBJECT
                                   | bullet.CollisionFlags.CF_STATIC_OBJECT)
        print(self.o1.collision_flags)
        self.assertEquals(self.o1.collision_flags
                          & bullet.CollisionFlags.CF_KINEMATIC_OBJECT,
                          2)
        self.assertEquals(self.o1.collision_flags
                          & bullet.CollisionFlags.CF_STATIC_OBJECT,
                          1)

    def test_user_index(self):
        self.o1.user_index = 1002
        self.assertEquals(self.o1.user_index, 1002)

    def tearDown(self):
        del self.o1
        del self.t1
        del self.v3
        del self.v1
        del self.v2
