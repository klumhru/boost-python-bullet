#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_dynamics.test_shapes
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class CollisionShapeTestCase(unittest.TestCase):
    def test_raise(self):
        def _instantiate_abstract():
            bullet.btCollisionShape()
        self.assertRaises(_instantiate_abstract)
