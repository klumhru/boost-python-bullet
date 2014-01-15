boost-python-bullet - Work in Progress!
===================
Trello: https://trello.com/b/pHVzGLi4/boost-python-bullet

This is a thin boost wrapper on top of Bullet Physics SDK (http://bulletphysics.org) - Note that I am not the owner of Bullet Physics SDK, nor am I affiliated with them. Bullet Physics SDK is under a separate license. See ./bullet_cpp/BulletLicense.txt for reference. There are some minor alterations in the source, specifically anonumous enums in classes are named so that they can be wrapped in a constructive way.

Feel free to contribute pull requests or post issues for discussion. Issues asking for ETAs on components will be closed without answers.

Unittests are mandatory for all pull requests. See the provided tests for reference. If you want to use a different test framework, it must be supported by nose. Unittests for the Bullet SDK itself are outside the scope of the project.

Also note the differences from reference in Bullet (see below), and calling conventions for pass-by-reference methods with primitive parameters (str, int, float, etc).

Also note that some constructors that take pointer parameters are implemented using factory methods, e.g. btDiscreteDynamicsWorld.

Serialization structures (e.g. btCompoundShapeData) are not wrapped. Serialization of these objects is beyond the scope of the project as it stands.

# Installation

I strongly recommend developing using virtualenv

Ubuntu: ```python-virtualenv```

CentOS: ```yum install python.pip``` and ```pip install virtualenv``` (use sudo)

## Dependencies

This library requires the boost libraries to be installed and the headers and shared libraries accessible. Version 1.35 and up should be supported (Boost.Python 2). It also requires the Python headers to be installed obviously.

It is recommended that you run the library from a virtualenv but a local installation should also work just fine.

The library has been built and tested on Linux (Ubuntu 12.04, 13.04, CentOS 5.1, 6.0). Windows and OSX builds should not be terribly problematic, but I won't ever support them myself.

## Setup

You can run
```
pip install -e git+git@github.com:Klumhru/boost-python-bullet.git#egg=boost-python-bullet
```
You can also download the current branch ```git clone git@github.com:Klumhru/boost-python-bullet.git``` and install by running ```python setup.py install.```

## Tests

The library is fully unit tested using python unittest. You can install nose and run nosetests in the root directory and nose should sniff out the tests in the various test folders.

# Usage

You can use the bullet physics manual for reference but

### Member functions

Member methods have been renamed to conform to python convention:

setRotation -> set_rotation
setValue -> set_value

### Properties / Data members

Some methods have been changed to properties, as in btVector3.length

By default "m_" style prefixes for public data members have been removed. In most cases "get_" prefixes have also been removed, with the exception of those that take arguments.

Example:

```C++
int btCompoundShape::getNumChildShapes() const
```
Becomes:
```Python
a.num_child_shapes # :int
```

On the other hand:
```C++
btCollisionShape* btCompoundShape::getChildShape(int)
```
Becomes:
```Python
a.get_child_shape(:int)
```

### Descriptive naming

Some methods have twins that have more descriptive names: btVector3.length_sqr
exists along with btVector3.length2 which is a property instead of a method as in
C++

### Const return values

Const return values are avoided where possible. Where methods have both implementations in CPP only the reference returning method is wrapped. This is intentional to avoid stack dumps that *will occur* when dealing with const ref instances in python if they are modified in python space.

The best way to study the use cases of the library is to read the (extensive) unittests.

### Primitives passed by reference

Where primitives are passed by reference as pseudo return values they are returned instead. This is because primitives are immutable in python. If more than one value is passed by reference they are returned as a tuple to maintain pythonity (new word, yay me).

## Implemented classes

Only a limited subset of the bullet library is wrapped so far. Work is ongoing.

Current classes that are fully wrapped (and tested):

* btQuadWord
* btQuaternion
* btTransform
* btTransformUtil
  * Note that some methods that take primitive values by reference return those values instead, as primitivees (e.g. float, int) are immutable in python. The affected methods are listed here:
    * calculate_diff_axis_angle_quaternion (btTransformUtil::calculateDiffAxisAngleQuaternion)
    * calculate_diff_axis_angle (btTransformUtil::calculateDiffAxisAngle)
* btVector3 (not btVector4)
* btMatrix3x3
* btMotionState / btDefaultMotionState
  * Note: check test_linear_math/test_motionstate.py for how to handle inheritance of btMotionState and implementing the virtual callback methods.
* btAlignedObjectArray - preliminary support
  * This class is meant for general data passing to and from the library and not for use by the developer. If you need methods exposed feel free to submit a pull request.
  * Many internal operations are not supported such as sorts and such. SDK internal callers usually call for sorting when they need it.
  * TODO: Add constructor from python list
  * TODO: Add more implementations - probably as I find them used in the libs
* btPoolAllocator
  * Only implemented to support some constructors and properties. It is not meant to be used by the developer using the library.
* btDbvtBroadphase
  * This is the default broadphase. Used to construct collision worlds
* btDefaultCollisionConfiguration
  * The default collision configuration
  * Includes btDefaultCollisionConstructionInfo used by its constructor
* btDiscreteDynamicsWorld
  * The default collision world
  * Implementation is limited while work on supporting objects is ongoing
* btCollisionShape
  * All shapes except complex mesh interface shapes are wrapped and tested
* btCollisionObject
* btRigidBody
  * Includes btRigidBodyConstructionInfo
  * Some functions are not yet wrapped as they rely on not-yet-implemented classes and functions
Bullet internals
====
Internals used for data transfer and internal logic are not exposed except where neccesary, and then without property implementations, and only limited constructors (or none at all). btDbvtNode and btDbvt are examples of this.

Common collection implementations of btAlignedObjectArray will be implemented for the exposed classes where applicable, e.g. btVector3, but not btDynamicsWorld. I you need something from the internals of Bullet, feel free to submit a pull request. Note that only requests with full tests will be merged.
