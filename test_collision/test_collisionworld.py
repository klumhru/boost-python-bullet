#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_collisionworld
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet

from .test_worlds import WorldTestDataMixin


class CollisionWorldTestCase(WorldTestDataMixin,
                             unittest.TestCase):
    def setUp(self):
        super(CollisionWorldTestCase, self).setUp()
        self.world = bullet.btCollisionWorld(self.dispatcher,
                                             self.broadphase,
                                             self.collision_config)

    def test_ctor(self):
        self.assertIsNotNone(self.dispatcher, "dispatcher is None...")

    def test_broadphase(self):
        self.world.broadphase = self.broadphase
        self.broadphase = self.world.broadphase
        self.assertIsNotNone(self.world.broadphase)
        self.assertIsNotNone(self.broadphase)

    def test_dispatcher(self):
        self.assertIsNotNone(self.world.dispatcher)

        # TODO: This segfaults by deleting the reference for world's instance
        # self.dispatcher = None

        d = self.world.dispatcher

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

