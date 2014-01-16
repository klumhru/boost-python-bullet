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
