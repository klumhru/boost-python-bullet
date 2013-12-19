#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
linear_math_tests.test_matrix3x3
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class TestMatrix3x3(unittest.TestCase):
    def setUp(self):
        self.v1 = tuple(float(i) for i in range(0, 9))
        self.v2 = tuple(2*i for i in self.v1)
        self.v_sqr = tuple(math.pow(i, 2) for i in self.v1)
        self.a = bullet.btMatrix3x3()
        self.b = bullet.btMatrix3x3()
        self.c = bullet.btMatrix3x3()
        self.d = bullet.btMatrix3x3()

    def test_constructors(self):
        self.a = bullet.btMatrix3x3(bullet.btQuaternion.identity)
        self.b = bullet.btMatrix3x3(self.a)
        self.c = bullet.btMatrix3x3(0, 0, 0,
                                    0, 0, 0,
                                    1, 1, 1)

    def test_str(self):
        self.a = bullet.btMatrix3x3(0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0)
        self.b = bullet.btMatrix3x3(self.a)
        s = str(self.a)
        t = repr(self.b)
        e = "((0, 0, 0), (0, 0, 0), (0, 0, 0))"
        self.assertEqual(s, t)
        self.assertEqual(s, e)

    def test_index(self):
        v = [float(i) for i in range(0, 9)]
        self.a = bullet.btMatrix3x3(*tuple(v))
        self.assertEqual(self.a[0], bullet.btVector3(*tuple(v[:3])))
        self.assertEqual(self.a[1], bullet.btVector3(*tuple(v[3:-3])))
        w = [4, 5, 6]
        self.a[0] = bullet.btVector3(*tuple(w))
        self.assertEqual(self.a[0], bullet.btVector3(*tuple(w)))

    def test_eq(self):
        v = tuple(float(i) for i in range(0, 9))
        self.a = bullet.btMatrix3x3(*v)
        self.b = bullet.btMatrix3x3(*tuple(reversed(v)))
        self.assertFalse(self.a == self.b)
        self.c = bullet.btMatrix3x3(self.a)
        self.assertEqual(self.a, self.c)

    def test_add(self):
        self.a = bullet.btMatrix3x3(*self.v1)
        self.b = bullet.btMatrix3x3(self.a)
        self.c = self.a + self.b
        self.a += self.b
        self.d = bullet.btMatrix3x3(*self.v2)
        self.assertEqual(self.a, self.c)
        self.assertEqual(self.a, self.d)

    def test_mul(self):
        self.a = bullet.btMatrix3x3(*self.v1)
        self.d = self.a * self.a
        self.a *= self.a
        self.assertEqual(self.a, self.d)

    def test_sub(self):
        self.a = bullet.btMatrix3x3(*self.v1)
        self.b = bullet.btMatrix3x3(*self.v2)
        self.c = self.b - self.a
        self.b -= self.a
        self.assertEqual(self.a, self.b)
        self.assertEqual(self.b, self.c)

    def tearDown(self):
        del self.a
        del self.b
        del self.c
        del self.d
        del self.v1
        del self.v2
