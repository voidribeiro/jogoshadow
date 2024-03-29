#ifndef _ABSTRACTCOMPONENT_H_
#define _ABSTRACTCOMPONENT_H_

#include "ComponentTypes.h"
#include "GameObject.h"
#include "LuaBinder.h"

class GameObject;

class AbstractComponent{
  protected:
    //Parent is used to get atributes or call methods within in
    //but the cross dependency of class is a bad thing, isn't?
    GameObject* parent;
  public:
    explicit AbstractComponent (){parent = NULL;};
    virtual ~AbstractComponent(){};
    virtual void SetParent(GameObject* parent) { this->parent = parent; };
    virtual int GetType() = 0;
    const virtual char* GetTypeName() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif 