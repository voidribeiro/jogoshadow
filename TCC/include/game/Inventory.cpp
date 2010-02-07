#include "Inventory.h"

Inventory::Inventory(){
}

Inventory::~Inventory(){
  map<std::string,GameObject*>::iterator i;
  for( i = items.begin(); i!=items.end(); ++i){
    (*i).second->RemoveAllComponents();
    (*i).second->~GameObject();
  }

}

void Inventory::Add(std::string objName, GameObject* obj){
  items[objName] = obj;
}

void Inventory::Remove(std::string objName){
   GameObject* obj =  items[objName];
   obj->RemoveAllComponents();
   obj->~GameObject();
}

GameObject* Inventory::getGameObject(std::string objName){
  return items[objName];
}