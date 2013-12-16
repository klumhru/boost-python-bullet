#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
linear_math_tests.test_transform
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class TestTransform(unittest.TestCase):
    def setUp(self):
        self.a = bullet.btTransform()
        self.b = bullet.btTransform()
        self.c = bullet.btTransform()
        self.d = bullet.btTransform()
        self.e = bullet.btTransform()
        self.v1 = tuple(float(i) for i in range(0, 9))
        self.vec = bullet.btVector3(0, 0, 0)
        self.q = bullet.btQuaternion.identity

    def test_ctors(self):
        self.a = bullet.btTransform(bullet.btMatrix3x3(*self.v1))
        self.b = bullet.btTransform(bullet.btMatrix3x3(*self.v1),
                                    bullet.btVector3(0, 0, 0))
        self.c = bullet.btTransform(bullet.btQuaternion.identity)
        self.d = bullet.btTransform(bullet.btQuaternion.identity,
                                    bullet.btVector3(0, 0, 0))
        self.assertEqual(self.a, self.b)

    def test_str(self):
        self.a = bullet.btTransform(self.q)
        self.b = bullet.btTransform(self.q)
        self.assertEqual(self.a, self.b)

    def tearDown(self):
        del self.a
        del self.b
        del self.c
        del self.d
        del self.e
