#ifndef __COMPONENTIMAGE_H__
#define __COMPONENTIMAGE_H__

#include "AbstractComponent.h"

class ComponentImage : public AbstractComponent{
  public:
    explicit ComponentImage();
    virtual ~ComponentImage();
    int GetType();
};

#endif