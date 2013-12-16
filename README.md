boost-python-bullet
===================
This is a thin boost wrapper on top of Bullet Physics SDK (http://bulletphysics.org)

It exposes a limited subset of classes.

You can use the bullet physics manual for reference but member methods have been
renamed to conform to python convention:

setRotation -> set_rotation
setValue -> set_value
etc...

Also some methods have been changed to properties, as in btVector3.length

Some methods have twins that have more descriptive names: btVector3.length_sqr
exists along with btVector3.length which is a property instead of a method as in
C++

### implemented classes

Only a limited subset of the bullet library is wrapped so far. Work is ongoing.

Current classes that are fully wrapped:

* btQuadWord
* btQuaternion
* btVector3 (btVector4)
