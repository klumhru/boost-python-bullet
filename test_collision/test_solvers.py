#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_collision.test_solvers
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class SequentialImpulseConstraintSolverTestCase(unittest.TestCase):
    def setUp(self):
        self.solver = bullet.btSequentialImpulseConstraintSolver()

    def test_ctor(self):
        pass

    def tearDown(self):
        del self.solver
