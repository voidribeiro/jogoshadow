#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "AbstractComponent.h"

#include <List>

using namespace std;

class GameObject{
  private:  
    list<AbstractComponent*> componentList;
  public:
    explicit GameObject ();
    virtual ~GameObject();
    void AddComponent(AbstractComponent* component);
    void RemoveAllComponents();
    void RemoveComponent(int componentType);
    void RemoveComponentByIndex(int index);
    int GetComponentsCount();
    AbstractComponent* GetComponent(int componentType);
    AbstractComponent* GetComponentByIndex(int index);
};

#endif