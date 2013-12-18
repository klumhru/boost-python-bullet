#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
linear_math_tests.test_transformutil
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class ClassTestName(unittest.TestCase):
    def setUp(self):
        self.q = bullet.btQuaternion.identity
        self.v = bullet.btVector3(0, 0, 0)
        self.a = bullet.btTransform.identity
        self.b = bullet.btTransform.identity

    def test_integrate_transform(self):
        bullet.btTransformUtil.integrate_transform(
            bullet.btTransform.identity,
            bullet.btVector3(0, 0, 10),
            bullet.btVector3(0, 0, 0),
            1.0/60,
            self.a  # out param
        )
        self.b = bullet.btTransform.identity
        self.b.set_origin(bullet.btVector3(0, 0, 10*(1.0/60)))
        self.assertEqual(self.a,
                         self.b)

    def tearDown(self):
        del self.a
        del self.b
        del self.q
        del self.v
