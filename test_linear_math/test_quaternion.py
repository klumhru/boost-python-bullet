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

    def test_add(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        q1 = bullet.btQuaternion(0, 0, 0, 1)
        self.q += q1
        self.assertEqual(self.q, bullet.btQuaternion(0, 0, 0, 2))
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        q1 = bullet.btQuaternion(0, 0, 0, 1)
        q2 = self.q + q1
        self.assertEqual(q2, bullet.btQuaternion(0, 0, 0, 2))

    def test_sub(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        q1 = bullet.btQuaternion(0, 0, 0, 1)
        self.q -= q1
        self.assertEqual(self.q, bullet.btQuaternion(0, 0, 0, 0))
        self.q = bullet.btQuaternion(0, 0, 0, 2)
        q1 = bullet.btQuaternion(0, 0, 0, 1)
        q2 = self.q - q1
        self.assertEqual(q2, q1)

    def test_nearest_farthest(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        q1 = bullet.btQuaternion(0, 0, 0, 2)
        nearest = self.q.nearest(q1)
        farthest = self.q.farthest(q1)
        # TODO: Add asserts

    def test_slerp(self):
        self.q = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                     bullet.btRadians(90))
        q1 = bullet.btQuaternion(bullet.btVector3(0, 0, -1), 0)
        q2 = self.q.slerp(q1, 0.5)
        expected = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                       bullet.btRadians(45))
        self.assertAlmostEqual(q2.angle(expected), 0)

    def test_identity(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        self.assertEqual(self.q, bullet.btQuaternion.get_identity())
        self.assertEqual(self.q, bullet.btQuaternion.identity)

    def test_neg(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        self.q -= bullet.btQuaternion(0, 0, 0, 2)
        self.assertEqual(self.q, -bullet.btQuaternion(0, 0, 0, 1))

    def test_mul(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        self.q *= 10.0
        self.assertEqual(self.q, bullet.btQuaternion(0, 0, 0, 10.0))
        self.q *= bullet.btQuaternion(0, 0, 0, 0.5)
        self.assertEqual(self.q, bullet.btQuaternion(0, 0, 0, 5.0))
        q1 = self.q * 2.0
        self.assertEqual(q1, bullet.btQuaternion(0, 0, 0, 10))

    def test_div(self):
        self.q = bullet.btQuaternion(0, 0, 0, 1)
        self.q /= 0.5
        self.assertEqual(self.q, bullet.btQuaternion(0, 0, 0, 2))
        q1 = self.q / 0.5
        self.assertEqual(q1, bullet.btQuaternion(0, 0, 0, 4))

    def test_dot(self):
        self.q = bullet.btQuaternion(0, 0, 20, 0)
        self.assertEqual(self.q.dot(bullet.btQuaternion(0, 0, 10, 0)),
                         200.0)

    def test_normalize(self):
        self.q = bullet.btQuaternion(0, 10, 20, 0)
        q1 = self.q.normalize()
        self.assertEqual(q1.length, q1.length2)
        self.assertAlmostEqual(self.q.length, 1)
        self.q = bullet.btQuaternion(0, 10, 20, 0)
        q1 = self.q.normalized()
        self.assertAlmostEqual(q1.length, 1.0)

    def test_angle(self):
        self.q = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                     bullet.btRadians(90))
        q1 = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                 bullet.btRadians(0))
        angle = self.q.angle(q1)
        expected = bullet.btRadians(45)
        self.assertAlmostEqual(angle, expected)
        angle = self.q.angle_shortest_path(q1)
        expected = bullet.btRadians(90)
        self.assertAlmostEqual(angle, expected)
        angle = self.q.get_angle()
        self.assertAlmostEqual(angle, bullet.btRadians(90))
        angle = self.q.get_angle_shortest_path()
        self.assertAlmostEqual(angle, bullet.btRadians(270))

    def test_axis(self):
        self.q = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                     bullet.btRadians(90))
        axis = self.q.get_axis()
        self.assertEqual(self.q.get_axis(), bullet.btVector3(0, 0, -1))

    def test_inverse(self):
        self.q = bullet.btQuaternion(bullet.btVector3(0, 0, 1),
                                     bullet.btRadians(90))
        q1 = bullet.btQuaternion(bullet.btVector3(0, 0, -1),
                                 bullet.btRadians(90))
        self.assertEqual(self.q, q1.inverse())

    def test_length(self):
        self.q = bullet.btQuaternion(0, 0, 2, 0)
        self.assertEqual(self.q.length, 2)
        self.assertEqual(self.q.length2, 4)

    def tearDown(self):
        del self.q
