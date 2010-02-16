/*

BMaths.h

Bone Maths

*/
#ifndef _BMATH_H_
#define _BMATH_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;

// rotates a bone
core::vector3df matrixRotation(core::vector3df rotation, core::vector3df vec);

#endif