#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
linear_math_tests.test_alignedobjectarray
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class ClassTestName(unittest.TestCase):
    def setUp(self):
        self.a = bullet.btVector3Array()
        for i in range(10):
            self.a.append(bullet.btVector3(i, i+1, i+2))
        self.b = bullet.btVector3Array()
        for i in range(10, 20):
            self.b.append(bullet.btVector3(i, i+1, i+2))

    def test_assignment(self):
        self.a[0] = bullet.btVector3(21, 22, 23)
        self.assertEqual(self.a[0],
                         bullet.btVector3(21, 22, 23))

        def _slice():
            self.a[0:3] = bullet.btVector3()

        self.assertRaises(RuntimeError, _slice)

    def tearDown(self):
        del self.a
        del self.b
