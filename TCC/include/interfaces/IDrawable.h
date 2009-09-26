#ifndef _IDRAWABLE_H_
#define _IDRAWABLE_H_

#include "constants/DrawableTypes.h"

class IDrawable{
  public:
     virtual void draw() = 0;
     virtual int getType() = 0;
     virtual ~IDrawable() {}
};

#endif