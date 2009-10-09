#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

//TODO - Implement all of this

void GameObject::AddComponent(AbstractComponent*){
}

void GameObject::RemoveComponent(int componentType){
}

void GameObject::RemoveComponentByIndex(int index){
}

int GameObject::GetComponentsCount(){
  return 0;
}
 
AbstractComponent* GameObject::GetComponent(int componentType){
  return NULL;
}

AbstractComponent* GameObject::GetComponentByIndex(int index){
  return NULL;
}
