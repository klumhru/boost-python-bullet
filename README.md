boost-python-bullet - Work in Progress!
===================
This is a thin boost wrapper on top of Bullet Physics SDK (http://bulletphysics.org)

# Installation

## Dependencies

This library requires the boost libraries to be installed and the headers and shared libraries accessible. Version 1.35 and up should be supported (Boost.Python 2). It also requires the Python headers to be installed obviously.

It is recommended that you run the library from a virtualenv but a local installation should also work just fine.

The library has only been built and tested on Linux (Ubuntu 12.04, 13.04, CentOS 5.1, 6.0)

## Setup

You can run pip install -e git+git@github.com:Klumhru/boost-python-bullet.git#egg=boost-python-bullet. You can also download the current branch and install by running python setup.py install.

## Tests

The library is fully unit tested using python unittest. You can install nose and run nosetests in the root directory and nose should sniff out the tests in the various test folders.

# Usage

You can use the bullet physics manual for reference but member methods have been
renamed to conform to python convention:

setRotation -> set_rotation
setValue -> set_value
etc...

Also some methods have been changed to properties, as in btVector3.length

Some methods have twins that have more descriptive names: btVector3.length_sqr
exists along with btVector3.length2 which is a property instead of a method as in
C++

The best way to study the use cases of the library is to read the (extensive) unittests.

### implemented classes

Only a limited subset of the bullet library is wrapped so far. Work is ongoing.

Current classes that are fully wrapped:

* btQuadWord
* btQuaternion
* btVector3 (not btVector4)
* btMatrix3x3
* btMotionState / btDefaultMotionState
  * Note: check linear_math_tests/test_motionstate.py for how to handle inheritance of btMotionState and implementing the virtual callback methods.

Internals used to data transfer and internal logic are not exposed. Common collection implementations of btAlignedObjectArray will be implemented for the exposed classes where applicable, e.g. btVector3, but not btDynamicsWorld.
