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
        self.t1 = bullet.btTransform.identity
        self.info = bullet.btRigidBodyConstructionInfo(
            1.0,
            self.motion_state,
            self.sphere_shape,
            self.inertia
        )

    def test_ctor(self):
        pass

    def test_motion_state(self):
        self.assertEquals(self.motion_state, self.info.motion_state)

    def tearDown(self):
        del self.info
        del self.t1
        del self.sphere_shape
        del self.inertia
        del self.radius
        del self.motion_state
