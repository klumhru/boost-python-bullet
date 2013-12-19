#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
linear_math_tests.test_motionstate
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class MyMotionState(bullet.btMotionState):
    def __init__(self):
        self.transform = bullet.btTransform.identity

    def setWorldTransform(self, t):
        self.transform = t

    def getWorldTransform(self, t):
        # Assign basis and origin as theres no way to assign by reference
        # as intended in the native method
        t.set_basis(self.transform.basis)
        t.set_origin(self.transform.origin)


class TestMotionState(unittest.TestCase):
    def setUp(self):
        self.m = bullet.btDefaultMotionState()

    def test_ctor(self):
        self.m = bullet.btDefaultMotionState()
        self.m = bullet.btDefaultMotionState(bullet.btTransform.identity)
        self.m = bullet.btDefaultMotionState(bullet.btTransform.identity,
                                             bullet.btTransform.identity)

        self.m = MyMotionState()

    def test_virtual(self):
        self.m = bullet.btMotionState()
        t1 = bullet.btTransform()
        self.assertRaises(RuntimeError, self.m.getWorldTransform, t1)

    def test_implemented(self):
        self.m = MyMotionState()
        t1 = bullet.btTransform(bullet.btQuaternion.identity,
                                bullet.btVector3(0, 10, 0))
        print('t1', t1)
        self.m.getWorldTransform(t1)
        self.assertEqual(t1, bullet.btTransform.identity)

    def tearDown(self):
        del self.m
