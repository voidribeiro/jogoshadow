#ifndef __ABSTRACTINTERACT_H__
#define __ABSTRACTINTERACT_H__

#include "AbstractComponent.h"

#include <string>

class ScriptObject;

class AbstractInteract : public AbstractComponent{
  public:  
    explicit AbstractInteract(){};
    virtual ~AbstractInteract(){};
    virtual int GetType() { return CINTERACT; };
    virtual const char* GetTypeName() { return "ComponentInteract"; };
    virtual void Interact() = 0;
    virtual void Interact(std::string object) = 0;
    virtual void Inspect() = 0;
};

#endif