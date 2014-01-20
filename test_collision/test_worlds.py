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

    def tearDown(self):
        del self.dispatcher
        del self.broadphase
        del self.collision_config
        del self.cinfo
        del self.solver


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
        self.broadphase = None
        self.assertIsNone(self.broadphase)
        self.broadphase = self.world.pair_cache
        self.assertIsNotNone(self.broadphase)

        def _should_raise():
            self.world.pair_cache = self.broadphase
        self.assertRaises(AttributeError, _should_raise)

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
