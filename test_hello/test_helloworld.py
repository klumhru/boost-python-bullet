#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
test_hello.test_helloworld
"""
from __future__ import unicode_literals, print_function, absolute_import

import unittest

import bullet


class HelloWorldTestCase(unittest.TestCase):
    """
    Basic hello world example implemented with the wrapper
    http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World
    """
    def setUp(self):
        self.time_step = 1.0/60.0
        self.broadphase = bullet.btDbvtBroadphase()
        self.collision_configuration = bullet.btDefaultCollisionConfiguration()
        self.dispatcher = bullet.btCollisionDispatcher(
            self.collision_configuration
        )
        self.solver = bullet.btSequentialImpulseConstraintSolver()
        self.dynamics_world = bullet.btDiscreteDynamicsWorld(
            self.dispatcher,
            self.broadphase,
            self.solver,
            self.collision_configuration
        )

    def test_hello_world(self):
        self.dynamics_world.gravity = bullet.btVector3(0, -9.8, 0)

    def test_add_sphere(self, pos=bullet.btVector3(0, 0, 0)):
        self.sphere_shape = bullet.btSphereShape(1)
        self.sphere_motion_state = bullet.btDefaultMotionState(
            bullet.btTransform(bullet.btQuaternion.identity,
                               pos)
        )
        self.sphere_mass = 1.0
        self.fall_inertia = bullet.btVector3(0, 0, 0)
        self.sphere_shape.calculate_local_inertia(self.sphere_mass,
                                                  self.fall_inertia)
        self.sphere_rigid_body_cinfo = bullet.btRigidBodyConstructionInfo(
            self.sphere_mass, self.sphere_motion_state, self.sphere_shape,
            self.fall_inertia
        )
        self.sphere_rigid_body = \
            bullet.btRigidBody(self.sphere_rigid_body_cinfo)
        self.dynamics_world.add_rigid_body(self.sphere_rigid_body)

    def test_add_ground(self):
        self.ground_shape = bullet.btStaticPlaneShape(
            bullet.btVector3(0, 1, 0), 1
        )
        self.ground_motion_state = bullet.btDefaultMotionState(
            bullet.btTransform(bullet.btQuaternion.identity,
                               bullet.btVector3(0, -1, 0))
        )
        self.ground_rigid_body_cinfo = bullet.btRigidBodyConstructionInfo(
            0, self.ground_motion_state, self.ground_shape,
            bullet.btVector3(0, 0, 0)
        )
        self.ground_rigid_body = \
            bullet.btRigidBody(self.ground_rigid_body_cinfo)
        self.dynamics_world.add_rigid_body(self.ground_rigid_body)

    def test_bodies(self):
        self.test_add_ground()
        self.test_add_sphere(bullet.btVector3(0, 50, 0))
        trans = bullet.btTransform.identity
        for i in range(300):
            self.dynamics_world.step_simulation(self.time_step)
            self.sphere_rigid_body.motion_state.get_world_transform(trans)
            print(trans.origin.y)
        self.assertAlmostEquals(trans.origin.y, 1.0)

    def tearDown(self):
        del self.dynamics_world
        del self.solver
        del self.dispatcher
        del self.collision_configuration
        del self.broadphase
