#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
tests
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class TestVector3(unittest.TestCase):
    def setUp(self):
        self.vec = bullet.btVector3()

    def test_exists(self):
        self.assertIsNotNone(self.vec)

    def test_props(self):
        two = 2.0
        self.vec.x = two
        self.vec.y = two
        self.vec.z = two
        self.assertEqual(self.vec.x, two)
        self.assertEqual(self.vec.y, two)
        self.assertEqual(self.vec.z, two)

        # test copy const reference
        x = self.vec.x
        x += 20
        self.assertFalse(self.vec.x == x)

    def test_overloaded_ctor(self):
        one = 1.0
        self.vec = bullet.btVector3(one, one, one)
        self.assertEqual(self.vec.x, one)
        self.assertEqual(self.vec.y, one)
        self.assertEqual(self.vec.z, one)

    def test_add(self):
        v1 = bullet.btVector3(1, 1, 1)
        v2 = bullet.btVector3(1, 1, 1)
        v = v1 + v2
        self.assertIsNotNone(v)
        self.assertEqual(v.x, 2.0)
        v = bullet.btVector3(v1 + v2)
        v1 += v2
        self.assertEqual(v, v1)

    def test_sub(self):
        v1 = bullet.btVector3(1, 1, 1)
        v2 = bullet.btVector3(1, 1, 1)
        v = v1 - v2
        self.assertIsNotNone(v)
        self.assertEqual(v.x, 0.0)
        v = bullet.btVector3(v1 - v2)
        v1 -= v2
        self.assertEqual(v1, v)

    def test_div(self):
        v1 = bullet.btVector3(2, 2, 2)
        v = v1 / 1.0
        self.assertEqual(v.x, 2)
        v /= 2
        self.assertEqual(v.x, 1)

    def test_mul(self):
        v1 = bullet.btVector3(2, 2, 2)
        v = v1 * 2.0
        self.assertEqual(v.x, 4)
        v *= 2.0
        self.assertEqual(v.x, 8)
        v2 = bullet.btVector3(2, 2, 2)
        v *= v2
        self.assertEqual(v.x, 16)

    def test_eq(self):
        v1 = bullet.btVector3(self.vec)
        self.assertEqual(self.vec, v1)
        self.assertEqual(self.vec.x, v1.x)
        self.assertFalse(self.vec != v1)
        self.assertTrue(self.vec == v1)

    def test_neg(self):
        v1 = bullet.btVector3(-self.vec)
        self.assertEqual(-v1.x, self.vec.x)

    def test_dot(self):
        v1 = bullet.btVector3(2, 2, 2)
        v2 = bullet.btVector3(v1)
        self.assertEqual(v1.dot(v2), 12.0)

    def test_length(self):
        v1 = bullet.btVector3(2, 2, 2)
        length2 = (math.pow(v1.x, 2) +
                   math.pow(v1.y, 2) +
                   math.pow(v1.z, 2))
        length = math.sqrt(length2)
        self.assertEqual(v1.length2, length2)
        self.assertEqual(v1.length, length)
        self.assertEqual(v1.norm, length)

    def test_distance(self):
        v1 = bullet.btVector3(2, 2, 2)
        v2 = bullet.btVector3(4, 4, 4)
        v = v2 - v1
        self.assertEqual(v1.distance(v2), v.length)
        self.assertEqual(v1.distance2(v2), v.length2)

    def tearDown(self):
        del self.vec
