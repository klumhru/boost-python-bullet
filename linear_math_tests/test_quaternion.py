#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
tests.test_quaternion
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class TestQuaternion(unittest.TestCase):
    def setUp(self):
        self.q = bullet.btQuaternion()

    def test_ctors(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        self.q = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                     bullet.btRadians(90))
        self.q = bullet.btQuaternion(0, 0, 0)

    def test_repr(self):
        self.q = bullet.btQuaternion(0, 0, 0)
        s = repr(self.q)
        self.assertEqual(s, "(0, 0, 0, 1)")

    def test_euler(self):
        self.q = bullet.btQuaternion(0, 0, 0)
        q1 = bullet.btQuaternion()
        q1.set_euler(0, 0, 0)
        self.assertEqual(self.q, q1)
        q1.set_euler_zyx(0, 0, 0)
        self.assertEqual(self.q, q1)

    def test_set_rotation(self):
        self.q = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                     bullet.btRadians(90))
        q1 = bullet.btQuaternion()
        q1.set_rotation(bullet.btVector3(0, 0, -1),
                        bullet.btRadians(90))
        self.assertEqual(self.q, q1)

    def tearDown(self):
        del self.q
