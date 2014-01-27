#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_worlds
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class WorldTestDataMixin(object):
    def setUp(self):
        self.solver = bullet.btSequentialImpulseConstraintSolver()
        self.cinfo = bullet.btDefaultCollisionConstructionInfo()
        self.collision_config = \
            bullet.btDefaultCollisionConfiguration(self.cinfo)
        self.broadphase = bullet.btDbvtBroadphase()
        self.dispatcher = bullet.btCollisionDispatcher(self.collision_config)
        self.gravity = bullet.btVector3(0, -9.8, 0)
        self.time_step = 1.0/60
        self.collision_object = bullet.btCollisionObject()
        self.v1 = bullet.btVector3(0, 0, 0)

    def tearDown(self):
        del self.v1
        del self.collision_object
        del self.dispatcher
        del self.broadphase
        del self.collision_config
        del self.cinfo
        del self.solver


class LocalRayResultTestCase(WorldTestDataMixin,
                             unittest.TestCase):
    def setUp(self):
        super(LocalRayResultTestCase, self).setUp()
        self.shape_info = bullet.LocalShapeInfo()
        self.shape_info.shape_part = 0
        self.shape_info.triangle_index = 0
        self.ray_result = bullet.LocalRayResult(self.collision_object,
                                                self.shape_info,
                                                self.v1,
                                                0.1)

    def test_ctor(self):
        pass

    def test_collision_object(self):
        self.assertIsNotNone(self.ray_result.collision_object)

    def tearDown(self):
        del self.ray_result
        del self.shape_info
        super(LocalRayResultTestCase, self).tearDown()
