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


class ConvexHullTestCase(unittest.TestCase):
    def setUp(self):
        # Describe a cube
        self.points = (
            bullet.btVector3(-1, -1, -1),
            bullet.btVector3(-1, 1, -1),
            bullet.btVector3(-1, -1, 1),
            bullet.btVector3(-1, 1, 1),
            bullet.btVector3(1, 1, 1),
            bullet.btVector3(1, -1, 1),
            bullet.btVector3(1, -1, -1),
            bullet.btVector3(1, 1, -1)
        )
        self.points_arr = bullet.btVector3Array()
        for p in self.points:
            self.points_arr.append(p)

    def test_empty_ctor(self):
        self.hull = bullet.btConvexHullShape()

    def test_list_ctor(self):
        self.hull = bullet.btConvexHullShape(list(self.points))
        self.assertEquals(self.hull.num_points, len(self.points))

    def test_num_points(self):
        self.test_list_ctor()
        self.assertEquals(self.hull.num_points, self.hull.get_num_points())
        self.assertEquals(self.hull.num_points, len(self.points))

    def test_tuple_ctor(self):
        self.hull = bullet.btConvexHullShape(self.points)
        self.assertEquals(self.hull.num_points, len(self.points))

    def test_array_ctor(self):
        self.hull = bullet.btConvexHullShape(self.points_arr)
        self.assertEquals(self.hull.num_points, len(self.points))

    def test_add_point(self):
        self.test_empty_ctor()
        for p in self.points:
            self.hull.add_point(p)
        self.assertEquals(self.hull.num_points, len(self.points))

    def test_get_unscaled_points(self):
        self.test_list_ctor()
        unscaled_points = self.hull.get_unscaled_points()
        self.assertTrue(isinstance(unscaled_points, bullet.btVector3Array))
        for i in range(len(self.points)):
            self.assertEquals(unscaled_points[i], self.points[i])

    def test_get_scaled_point(self):
        self.test_list_ctor()
        for i in range(len(self.points)):
            point = self.hull.get_scaled_point(i)
            self.assertEquals(self.points[i], point)

    def tearDown(self):
        if hasattr(self, 'hull'):
            del self.hull
        del self.points


class PolyhedralConvexAabbCachingTestCase(unittest.TestCase):
    """
    We use btConvexHullShape to implicitly test abstract base classes
    that it inherits and implements
    """
    def setUp(self):
        # tolerance reflects the internal penetration tolerance
        self.tolerance = bullet.btVector3(0.04, 0.04, 0.04)
        # Describe a cube
        self.points = [
            bullet.btVector3(-1, -1, -1),
            bullet.btVector3(-1, 1, -1),
            bullet.btVector3(-1, -1, 1),
            bullet.btVector3(-1, 1, 1),
            bullet.btVector3(1, 1, 1),
            bullet.btVector3(1, -1, 1),
            bullet.btVector3(1, -1, -1),
            bullet.btVector3(1, 1, -1)
        ]
        self.hull = bullet.btConvexHullShape(self.points)

    def test_ctor(self):
        pass

    def test_get_nonvirtual_aabb(self):
        aabb_min = bullet.btVector3()
        aabb_max = bullet.btVector3()
        trans = bullet.btTransform.identity
        self.hull.recalc_local_aabb()
        self.hull.get_nonvirtual_aabb(trans, aabb_min, aabb_max, 0.00)
        self.assertEquals(aabb_min, self.points[0] - self.tolerance)
        self.assertEquals(aabb_max, self.points[4] + self.tolerance)

    def test_get_aabb(self):
        aabb_min = bullet.btVector3()
        aabb_max = bullet.btVector3()
        trans = bullet.btTransform.identity
        self.hull.recalc_local_aabb()
        self.hull.get_aabb(trans, aabb_min, aabb_max)
        self.assertEquals(aabb_min, self.points[0] - self.tolerance*2)
        self.assertEquals(aabb_max, self.points[4] + self.tolerance*2)

    def test_local_scaling(self):
        scaling = bullet.btVector3(2, 2, 2)
        self.hull.set_local_scaling(scaling)
        self.points[0] *= scaling
        self.points[4] *= scaling
        self.test_get_aabb()

    def tearDown(self):
        del self.hull
        del self.points


class PolyhedralConvexTestCase(unittest.TestCase):
    """
    We use btConvexHullShape to implicitly test abstract base classes
    that it inherits and implements
    """
    def setUp(self):
        # Describe a cube
        self.points = [
            bullet.btVector3(-1, -1, -1),
            bullet.btVector3(-1, 1, -1),
            bullet.btVector3(-1, -1, 1),
            bullet.btVector3(-1, 1, 1),
            bullet.btVector3(1, 1, 1),
            bullet.btVector3(1, -1, 1),
            bullet.btVector3(1, -1, -1),
            bullet.btVector3(1, 1, -1)
        ]
        self.hull = bullet.btConvexHullShape(self.points)

    def test_ctor(self):
        pass

    def test_num_vertices(self):
        self.assertEquals(self.hull.num_vertices, 8)

    def test_num_edges(self):
        self.assertEquals(self.hull.num_edges, 8)

    def test_num_planes(self):
        self.assertEquals(self.hull.num_planes, 0)

    def test_is_inside(self):
        """
        is_inside is pure abstract and is never implemented in any class
        so we'll just assert it raises and move on
        """
        def _is_inside_call(vec, margin):
            self.hull.is_inside(vec, margin)

    def test_get_edge(self):
        pa = bullet.btVector3()
        pb = bullet.btVector3()
        self.hull.get_edge(0, pa, pb)
        self.assertEquals(pa, self.points[0])
        self.assertEquals(pb, self.points[1])

    def test_get_vertex(self):
        v = bullet.btVector3()
        for i in range(len(self.points)):
            self.hull.get_vertex(i, v)
            self.assertEquals(v, self.points[i])

    def test_get_plane(self):
        def _get_plane():
            normal = bullet.btVector3()
            support = bullet.btVector3()
            self.hull.get_plane(normal, support, 0)
        self.assertRaises(_get_plane)

    def tearDown(self):
        del self.hull
        del self.points
