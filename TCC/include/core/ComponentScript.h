#ifndef __COMPONENTSCRIPT_H__
#define __COMPONENTSCRIPT_H__

#include "AbstractComponent.h"

class ComponentScript : public AbstractComponent{
  public:
    explicit ComponentScript();
    virtual ~ComponentScript();
    int GetType();
};

#endif