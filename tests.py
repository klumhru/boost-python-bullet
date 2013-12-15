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
        self.vec = bullet.btVector3(0, 0, 0)

    def test_exists(self):
        self.assertIsNotNone(self.vec)

    def test_str(self):
        s = str(self.vec)
        self.assertEqual(s, "(0, 0, 0)")

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
        v3 = bullet.btVector3(v1)
        v4 = bullet.btVector3(v1)
        v = v4.dot3(v1, v2, v3)
        expected = bullet.btVector3(12, 12, 12)
        self.assertEqual(v, expected)

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

    def test_normalize(self):
        v1 = bullet.btVector3(2, 2, 2)
        v2 = v1.normalized
        v1.normalize()
        self.assertEqual(v1, v2)
        v1 = bullet.btVector3(1, 0, 0)
        v2 = bullet.btVector3(v1)
        self.assertEqual(v1.normalized, v2)

    def test_rotate(self):
        v1 = bullet.btVector3(0, 1, 0)  # up
        v2 = bullet.btVector3(0, 0, -1)  # forward
        expected = bullet.btVector3(1, 0, 0)  # right
        v = v1.rotate(v2, bullet.btRadians(90))
        self.assertAlmostEqual(v.x, expected.x)
        self.assertAlmostEqual(v.y, expected.y)
        self.assertAlmostEqual(v.z, expected.z)

    def test_minmax(self):
        v1 = bullet.btVector3(2, 4, 6)
        v2 = bullet.btVector3(1, 2, 3)
        v1.set_min(v2)
        self.assertEqual(v1, v2)
        v1 = bullet.btVector3(2, 4, 6)
        v2 = bullet.btVector3(1, 2, 3)
        v2.set_max(v1)
        self.assertEqual(v1, v2)
        v1 = bullet.btVector3(2, 4, 6)
        print('v1', v1)
        self.assertEqual(v1.min_axis, 0)
        self.assertEqual(v1.furthest_axis, 0)
        v2 = bullet.btVector3(3, 2, 1)
        print('v2', v2)
        self.assertEqual(v2.max_axis, 0)
        self.assertEqual(v2.closest_axis, 0)

    def test_setval(self):
        v1 = bullet.btVector3(1, 2, 3)
        v2 = bullet.btVector3(2, 4, 6)
        v1.set_value(2, 4, 6)
        self.assertEqual(v1, v2)
        v2.set_zero()
        zerovec = bullet.btVector3(0, 0, 0)
        self.assertEqual(v2, zerovec)
        self.assertTrue(v2.is_zero)
        self.assertTrue(v2.fuzzy_zero)

    def test_abs(self):
        v1 = bullet.btVector3(1, 2, 3)
        v2 = bullet.btVector3(v1)
        v = v1.absolute()
        self.assertEqual(v, abs(v2))
        self.assertEqual(v, v1)

    def test_angle(self):
        v1 = bullet.btVector3(1, 0, 0)
        v2 = bullet.btVector3(0, 1, 0)
        self.assertEqual(v1.angle(v2), bullet.btRadians(90))

    def test_cross(self):
        v1 = bullet.btVector3(1, 0, 0)
        v2 = bullet.btVector3(0, 1, 0)
        v = v1.cross(v2)
        expected = bullet.btVector3(0, 0, 1)
        self.assertEqual(v, expected)

    def test_interpolate(self):
        v1 = bullet.btVector3(0, 1, 0)
        v2 = bullet.btVector3(1, 0, 0)
        v3 = bullet.btVector3(0, 0, 0)
        v3.set_interpolate_3(v1, v2, 0.5)
        expected = bullet.btVector3(0.5, 0.5, 0)
        self.assertEqual(v3, expected)
        v3 = v1.lerp(v2, 0.5)
        expected = bullet.btVector3(0.5, 0.5, 0)
        self.assertEqual(v3, expected)

    def tearDown(self):
        del self.vec
