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
        self.v1 = tuple(float(i) for i in range(0, 9))
        self.vec = bullet.btVector3(0, 0, 0)
        self.q = bullet.btQuaternion.identity
        self.m = bullet.btMatrix3x3(*self.v1)

        self.a = bullet.btTransform()
        self.b = bullet.btTransform()
        self.c = bullet.btTransform()
        self.d = bullet.btTransform()
        self.e = bullet.btTransform()

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

    def test_mult(self):
        self.a = bullet.btTransform(self.q)
        self.b = bullet.btTransform(bullet.btQuaternion(1, 1, 0, 0))
        self.c = bullet.btTransform(self.q)
        self.c.mult(self.a, self.b)
        self.assertFalse(self.c == self.a)

    def test_basis(self):
        self.a = bullet.btTransform(self.m)
        self.assertEqual(self.a.get_basis(), self.m)
        w = (4, 5, 6)
        self.a.basis[0] = bullet.btVector3(*w)
        self.assertFalse(self.a.get_basis() == self.m)
        self.a.set_basis(self.m)
        self.assertEqual(self.a.get_basis(), self.m)

    def test_rotation(self):
        self.a = bullet.btTransform(self.q)
        self.assertEqual(self.a.get_rotation(), self.q)
        self.q = bullet.btQuaternion(0, 1, 1, 0)
        self.assertNotEqual(self.q, self.a.get_rotation())
        self.a.set_rotation(self.q)
        print(self.q.normalized(), self.a.get_rotation())
        # Hack to bypass numeric imprecision
        # TODO: Extend test case to implement assertAlmostEqual with matrices
        self.assertTrue(str(self.q.normalized()) == str(self.a.get_rotation()))

    def test_origin(self):
        self.a = bullet.btTransform(self.q)
        self.b = bullet.btTransform(self.q)
        self.vec = self.a.get_origin()
        self.assertEqual(self.vec, self.a.get_origin())
        self.assertEqual(self.a.get_origin(), bullet.btVector3(0, 0, 0))
        self.a.origin.set_value(1, 0, 0)
        self.assertEqual(self.a.get_origin(), bullet.btVector3(1, 0, 0))
        self.a.set_origin(bullet.btVector3(0, 1, 0))
        self.assertEqual(self.a.get_origin(), bullet.btVector3(0, 1, 0))

    def test_identit(self):
        self.a = bullet.btTransform.identity
        self.b = bullet.btTransform(bullet.btQuaternion(1, 0, 0, 0),
                                    bullet.btVector3(0, 1, 0))
        self.assertEqual(self.a.get_rotation(), bullet.btQuaternion.identity)
        self.assertEqual(self.a.get_origin(), self.vec)
        print(self.b.get_origin(), self.vec)
        self.assertFalse(self.b.get_origin() == self.vec)
        self.b.set_identity()
        self.assertEqual(self.a, self.b)
        self.assertEqual(bullet.btTransform.identity, self.a)

    def test_inverse(self):
        self.a = bullet.btTransform(self.q, bullet.btVector3(0, 0, 1))
        self.b = bullet.btTransform(self.q, bullet.btVector3(0, 0, -1))
        self.c = self.a.inverse()
        self.d = bullet.btTransform(bullet.btQuaternion.identity,
                                    bullet.btVector3(1, 0, 0))
        self.assertEqual(self.b, self.c)
        self.vec = self.d.inv_xform(bullet.btVector3(0, 1, 0))
        self.assertEqual(self.vec, bullet.btVector3(-1, 1, 0))
        self.e = self.b.inverse_times(self.a)
        self.assertEqual(self.e, bullet.btTransform(
                         bullet.btQuaternion.identity,
                         bullet.btVector3(0, 0, 2)))

    def test_mul(self):
        self.a = bullet.btTransform.identity
        self.b = bullet.btTransform.identity
        self.a.set_origin(bullet.btVector3(1, 1, 1))
        self.c = self.a * self.b
        self.a *= self.b
        self.assertEqual(self.c, self.a)

    def tearDown(self):
        del self.a
        del self.b
        del self.c
        del self.d
        del self.e
