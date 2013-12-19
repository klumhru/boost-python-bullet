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
        self.q1 = bullet.btQuaternion.identity
        self.q2 = bullet.btQuaternion.identity
        self.v1 = bullet.btVector3(0, 0, 0)
        self.v2 = bullet.btVector3(0, 0, 10)
        self.t1 = bullet.btTransform.identity
        self.t2 = bullet.btTransform.identity
        self.step = 1.0/60

    def test_integrate_transform(self):
        bullet.btTransformUtil.integrate_transform(
            self.t2,
            self.v2,
            self.v1,
            1.0/60,
            self.t1  # out param
        )
        self.t2 = bullet.btTransform.identity
        self.t2.set_origin(bullet.btVector3(0, 0, 10*(self.step)))
        self.assertEqual(self.t1,
                         self.t2)

    def test_calculate_velocity_quaternion(self):
        self.q2.set_euler(0,
                          bullet.btRadians(90),
                          0)
        lin_vel = bullet.btVector3(0, 0, 0)
        ang_vel = bullet.btVector3(0, 0, 0)
        bullet.btTransformUtil.calculate_velocity_quaternion(
            self.v1,
            self.v2*self.step,
            self.q1,
            self.q2,
            self.step,
            lin_vel,  # out param
            ang_vel   # out param
        )
        print('lin_vel', lin_vel)
        print('ang_vel', ang_vel)
        print('ang_vel.x degrees', bullet.btRadians(ang_vel.x))
        self.assertEqual(lin_vel, self.v2)

    def test_calculate_diff_axis_angle_quaternion(self):
        self.q2.set_rotation(bullet.btVector3(0, 0, -1),
                             bullet.btRadians(90))
        angle = bullet.btRadians(0.0)
        angle = bullet.btTransformUtil.calculate_diff_axis_angle_quaternion(
            self.q1,
            self.q2,
            self.v1
        )
        self.assertFalse(angle == 0.0)
        self.assertEqual(angle, bullet.btRadians(90))

    def test_calculate_velocity(self):
        self.t2.set_origin(self.v2)
        bullet.btTransformUtil.calculate_velocity(
            self.t1, self.t2, self.step,
            self.v1,  # linVel
            self.v2   # angVel
        )
        self.assertEqual(self.v1, self.t2.origin/self.step)
        self.assertEqual(self.v2, bullet.btVector3(0, 0, 0))

    def test_calculate_diff_axis_angle(self):
        self.v1 = bullet.btVector3(0, 0, -1)
        self.q1 = bullet.btQuaternion(self.v1,
                                      bullet.btRadians(90))
        self.t2.set_rotation(self.q1)
        angle = bullet.btTransformUtil.calculate_diff_axis_angle(
            self.t1, self.t2,
            self.v2  # out val
        )
        self.assertEqual(angle, bullet.btRadians(90))
        self.assertEqual(self.v1, self.v2)

    def tearDown(self):
        del self.t1
        del self.t2
        del self.q1
        del self.q2
        del self.v1
        del self.v2
