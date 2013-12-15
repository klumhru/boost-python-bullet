#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
tests
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest
import math

import bullet


class TestQuadWord(unittest.TestCase):
    def setUp(self):
        self.word = bullet.btQuadWord()

    def test_constructors(self):
        self.word = bullet.btQuadWord(0, 0, 0)
        self.word = bullet.btQuadWord(0, 0, 0, 0)

    def test_properties(self):
        self.word.x = 1.0
        self.assertEqual(self.word.x, 1.0)
        self.word.y = 2.0
        self.assertEqual(self.word.y, 2.0)
        self.word.z = 3.0
        self.assertEqual(self.word.z, 3.0)
        self.word.w = 0.0
        self.assertEqual(self.word.w, 0.0)

    def test_eq(self):
        self.word = bullet.btQuadWord(1, 1, 1)
        self.assertEqual(self.word, bullet.btQuadWord(1, 1, 1))
        self.assertFalse(self.word != bullet.btQuadWord(1, 1, 1))

    def test_str(self):
        self.word = bullet.btQuadWord(1, 1, 1)
        s = str(self.word)
        self.assertEqual(s, "(1, 1, 1, 0)")

    def test_set_value(self):
        self.word = bullet.btQuadWord(1, 1, 1)
        self.word.set_value(2, 2, 2)
        self.assertEqual(self.word, bullet.btQuadWord(2, 2, 2))
        self.assertEqual(self.word.w, 0)
        self.word.set_value(5, 5, 5, 5)
        self.assertEqual(self.word, bullet.btQuadWord(5, 5, 5, 5))
        self.assertEqual(self.word.w, 5)

    def test_minmax(self):
        self.word = bullet.btQuadWord(4, 2, 3)
        self.word.set_min(bullet.btQuadWord(1, 3, 2))
        self.assertEqual(self.word, bullet.btQuadWord(1, 2, 2))
        self.word.set_max(bullet.btQuadWord(3, 5, 1))
        self.assertEqual(self.word, bullet.btQuadWord(3, 5, 2))

    def tearDown(self):
        del self.word
