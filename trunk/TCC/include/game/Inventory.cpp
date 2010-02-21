#include "Inventory.h"

Inventory::Inventory(){
  //setBackground(backgroundImageName);
  setVisible(false);
}

Inventory::~Inventory(){
  std::map<std::string,GameObject*>::iterator i;
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
  if (lastVisible!=isVisible){
    if (isVisible){
      CreateInventoryButtons();
    }
    else
    {
      RemoveInventoryButtons();
    }
  }

  lastVisible = isVisible;

  if (!isVisible)
    return;

  std::map<std::string,GameObject*>::iterator it;
  for(it = items.begin(); it!=items.end(); it++){
    if ((*it).second != NULL){
      if (((irr::gui::IGUIButton*)inventoryButtons[(*it).first])->isPressed()){
        //ComponentInteract* cInteract = (ComponentInteract*)(*it).second->GetComponent(CINTERACT);
        //cInteract->Interact();
        setVisible(false);
      }
    }
  }
  //irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  //driver->draw2DImage(backgroundImage, core::position2d<s32>(0,0));
}

void Inventory::CreateInventoryButtons(){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();
  
  irr::gui::IGUIElement* back = env->addImage(backgroundImage, 
                  core::position2d<s32>(0, 0),
                  true, 0, 5 );
  inventoryButtons["INVENTORY_BACKGROUND"] = back;

  int numCols = 5;
  int offsetX = 110;
  int offsetY = 110;
  int offX = -50;
  int offY = -50;
  
  int itemNum = 0;
  std::map<std::string,GameObject*>::iterator it;
  for( it = items.begin(); it!=items.end(); it++){
    if ((*it).second != NULL){
      GameObject* gO = (*it).second;  
      ComponentImage* cImage = (ComponentImage*)(gO->GetComponent(CIMAGE));

      
      float posX = ((itemNum % 5) + 1) * offsetX + offX;
      float posY = (irr::core::abs_(itemNum/5)+1) * offsetY + offY;

      itemNum++;

      ITexture* tex = TextureManager::GetTexture(cImage->GetFileName());
      irr::gui::IGUIButton* buf = env->addButton( core::rect<s32>(posX, posY, 
                                                 posX + 100,
                                                 posY + 100) );

      //adicina o parent na imagem
      buf->setImage(tex);

      inventoryButtons[(*it).first] = buf;
    }
  }
}

void Inventory::RemoveInventoryButtons(){
  std::map<std::string,IGUIElement*>::iterator it;
  for(it = inventoryButtons.begin(); it!=inventoryButtons.end(); it++){
    (*it).second->remove();
  }
  inventoryButtons.clear();
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