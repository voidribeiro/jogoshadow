#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "AbstractComponent.h"

#include <List>

class GameObject{
  private:
  public:
    explicit GameObject ();
    virtual ~GameObject();
    //AbstractComponent* GetComponent();

    //TODO - This is for test only
    AbstractComponent* abstractComponent;
};

#endif