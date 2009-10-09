#ifndef __ABSTRACTCOMPONENT_H__
#define __ABSTRACTCOMPONENT_H__

#include "ComponentTypes.h"
#include "GameObject.h"
#include "LuaBinder.h"

class GameObject;

class AbstractComponent{
  private:
    //Parent is used to get atributes or call methods within in
    //but the cross dependency of class is a bad thing, isn't?
    GameObject* parent;
  public:
    explicit AbstractComponent (){};
    virtual ~AbstractComponent(){};
    void SetParent(GameObject* parent) { this->parent = parent; };
    virtual int GetType() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif