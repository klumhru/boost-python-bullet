#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_collisiondispatcher
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class CollisionDispatcherTestCase(unittest.TestCase):
    def setUp(self):
        self.cinfo = bullet.btDefaultCollisionConstructionInfo()
        self.config = bullet.btDefaultCollisionConfiguration(self.cinfo)
        self.cd = bullet.btCollisionDispatcher(self.config)

    def test_ctor(self):
        pass

    def tearDown(self):
        del self.cd
        del self.config
        del self.cinfo
