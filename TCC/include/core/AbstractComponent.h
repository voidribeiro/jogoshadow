#ifndef __ABSTRACTCOMPONENT_H__
#define __ABSTRACTCOMPONENT_H__

#include "ComponentTypes.h"

class AbstractComponent{
  private:
  public:
    explicit AbstractComponent (){};
    virtual ~AbstractComponent(){};
    virtual int GetType() = 0;
};

#endif