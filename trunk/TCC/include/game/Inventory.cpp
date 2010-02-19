#include "Inventory.h"

Inventory::Inventory(){
  //setBackground(backgroundImageName);
}

Inventory::~Inventory(){
  map<std::string,GameObject*>::iterator i;
  for( i = items.begin(); i!=items.end(); ++i){
    (*i).second->RemoveAllComponents();
    (*i).second->~GameObject();
  }

  delete backgroundImage;

}

void Inventory::add( GameObject* obj){
  ComponentImage* cImage = (ComponentImage*) obj->GetComponent(CIMAGE);

  if (cImage == NULL){
    printf("Missing Image Reference\n");
    return;
  }

  items[obj->GetName()] = obj;
}

void Inventory::remove(std::string objName){
   GameObject* obj =  items[obj->GetName()];
   obj->RemoveAllComponents();
   obj->~GameObject();
}

bool Inventory::isInInventory( std::string objName ){
  return (items[objName] != NULL);
}


GameObject* Inventory::getGameObject(std::string objName){
  return items[objName];
}

void Inventory::setBackground(std::string filename){
  backgroundImage = TextureManager::GetTexture(filename);
}

void Inventory::setVisible(bool visible){
  isVisible = visible;
}

void Inventory::draw(){
  if (!isVisible)
    return;
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  driver->draw2DImage(backgroundImage, core::position2d<s32>(0,0));
}


ComponentModel* Inventory::getComponentModel(std::string objName){
  ComponentModel* cModel = (ComponentModel*)items[objName]->GetComponent(CMODEL);
  if (cModel == NULL)
    printf("Missing Model Reference\n");

  return cModel;
}


ComponentImage* Inventory::getComponentImage(std::string objName){
  ComponentImage* cImage = (ComponentImage*)items[objName]->GetComponent(CIMAGE);
  if (cImage == NULL)
    printf("Missing Image Reference\n");

  return cImage;
}