#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_hello.test_hello
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class HelloTestCase(unittest.TestCase):
    def setUp(self):
        self.hello = bullet.Hello()
        self.data = bullet.Data()

    def test_ctor(self):
        pass

    def test_data(self):
        self.hello.data = self.data
        data = self.hello.data
        data.a = 1
        data2 = bullet.Data()
        data2.a = 1
        self.hello.data = data2
        self.assertEquals(self.hello.data, data2)

    def tearDown(self):
        del self.data
        del self.hello
