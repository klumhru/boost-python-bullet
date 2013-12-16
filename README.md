boost-python-bullet
===================
This is a thin boost wrapper on top of Bullet Physics SDK (http://bulletphysics.org)

It exposes a limited subset of classes.

You can use the bullet physics manual for reference but member methods have been renamed to python notation:

setRotation -> set_rotation
setValue -> set_value

etc...

### implemented classes

Only a limited subset of the bullet library is wrapped so far. Work is ongoing.

Current classes that are fully wrapped:

* btQuadWord
* btQuaternion
* btVector3 (btVector4)
