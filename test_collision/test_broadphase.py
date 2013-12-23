#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_broadphase
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import bullet


class TestBroadPhase(unittest.TestCase):
    def setUp(self):
        self.bp = bullet.btDbvtBroadphase()

    def test_ctor(self):
        self.bp = bullet.btDbvtBroadphase()

    def tearDown(self):
        del self.bp
