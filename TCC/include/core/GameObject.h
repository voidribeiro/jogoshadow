#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "AbstractComponent.h"

#include <List>

class GameObject{
  private:  
    std::list<AbstractComponent*> componentList;
  public:
    explicit GameObject ();
    virtual ~GameObject();
    void AddComponent(AbstractComponent*);
    void RemoveComponent(int componentType);
    void RemoveComponentByIndex(int index);
    int GetComponentsCount();
    AbstractComponent* GetComponent(int componentType);
    AbstractComponent* GetComponentByIndex(int index);
};

#endif