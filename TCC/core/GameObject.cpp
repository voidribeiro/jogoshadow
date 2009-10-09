#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

//TODO - Implement all of this

void GameObject::AddComponent(AbstractComponent* component){
  componentList.push_back(component);
}

void GameObject::RemoveComponent(int componentType){
}

void GameObject::RemoveComponentByIndex(int index){
}

void GameObject::RemoveAllComponents(){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++)
    if ((*it) != NULL)
      delete (*it);
}

int GameObject::GetComponentsCount(){
  return componentList.size();
}
 
AbstractComponent* GameObject::GetComponent(int componentType){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++)
    if (((*it) != NULL) && ((*it)->GetType() == componentType))
        return (*it);
  return NULL;
}

AbstractComponent* GameObject::GetComponentByIndex(int index){
  return NULL;
}
