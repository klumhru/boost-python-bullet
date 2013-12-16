#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_linearmath.test_motionstate
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class MyMotionState(bullet.btMotionState):
    def __init__(self):
        self.world_transform = bullet.btTransform.identity

    def get_world_transform(self):
        return self.world_transform

    def set_world_transform(self, t):
        self.world_transform = t


class TestMotionState(unittest.TestCase):
    def setUp(self):
        self.m = bullet.btDefaultMotionState()

    def test_ctor(self):
        self.m = bullet.btDefaultMotionState()
        self.m = bullet.btDefaultMotionState(bullet.btTransform.identity)
        self.m = bullet.btDefaultMotionState(bullet.btTransform.identity,
                                             bullet.btTransform.identity)

        self.m = MyMotionState()

    def test_mystate(self):
        t = bullet.btTransform(bullet.btQuaternion.identity,
                               bullet.btVector3(0, 2, 0))
        self.m = MyMotionState()
        self.m.set_world_transform(t)
        self.assertEqual(self.m.get_world_transform(), t)

    def tearDown(self):
        del self.m
