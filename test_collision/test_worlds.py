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


class CollisionWorldTestCase(WorldTestDataMixin,
                             unittest.TestCase):
    def setUp(self):
        super(CollisionWorldTestCase, self).setUp()
        self.world = bullet.btCollisionWorld(self.dispatcher,
                                             self.broadphase,
                                             self.collision_config)

    def test_ctor(self):
        pass

    def test_broadphase(self):
        self.world.broadphase = self.broadphase
        self.broadphase = self.world.broadphase
        self.assertIsNotNone(self.world.broadphase)
        self.assertIsNotNone(self.broadphase)

    def test_dispatcher(self):
        self.assertIsNotNone(self.world.dispatcher)
        self.dispatcher = None
        self.assertIsNone(self.dispatcher)
        self.dispacher = self.world.dispatcher
        self.assertIsNotNone(self.dispacher)

        def _should_raise():
            self.world.dispatcher = self.dispacher
        self.assertRaises(AttributeError, _should_raise)

    def test_pair_cache(self):
        self.assertIsNotNone(self.world.pair_cache)
        self.broadphase = self.world.broadphase
        self.assertIsNotNone(self.broadphase)

        def _should_raise():
            self.world.pair_cache = None
        self.assertRaises(AttributeError, _should_raise)

    # TODO: Enable this after we can add/remove objects
#    def test_update_single_aabb(self):
#        self.world.update_single_aabb(self.collision_object)

    def test_update_aabbs(self):
        self.world.update_aabbs()

    def test_compute_overlapping_pairs(self):
        self.world.compute_overlapping_pairs()

    def tearDown(self):
        del self.world
        super(CollisionWorldTestCase, self).tearDown()


class DiscreteDynamicsWorldTestCase(WorldTestDataMixin,
                                    unittest.TestCase):
    def setUp(self):
        super(DiscreteDynamicsWorldTestCase, self).setUp()
        self.world = bullet.btDiscreteDynamicsWorld(
            self.dispatcher,
            self.broadphase,
            self.solver,
            self.collision_config
        )

    def test_ctor(self):
        pass

    def test_step(self):
        for i in range(120):
            self.world.step_simulation(self.time_step)

    def test_sync_states(self):
        for i in range(120):
            self.world.step_simulation(self.time_step)
            self.world.synchronize_motion_states()

    def test_gravity(self):
        self.world.set_gravity(self.gravity)
        self.assertEquals(self.world.gravity, self.gravity)
        self.world.gravity = bullet.btVector3(0, 0, 0)
        self.assertEquals(self.world.get_gravity(),
                          bullet.btVector3(0, 0, 0))
        self.assertEquals(self.world.gravity,
                          bullet.btVector3(0, 0, 0))

    def tearDown(self):
        del self.world
        super(DiscreteDynamicsWorldTestCase, self).tearDown()
