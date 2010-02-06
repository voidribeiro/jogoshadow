#include "Item.h"

Item::Item(){
}

Item::Item(string _name, bool _modelIsVisible, bool _isInPlayerPosession)
:name(_name), modelIsVisible(_modelIsVisible), imageIsVisible(false), isInPlayerPosession(_isInPlayerPosession){
}

Item::~Item(){
}

void Item::addDescription(const string description){
  descriptionList.push_back(description);
}

string Item::getDescription(const int idx){
  list<string>::iterator it;
  it = descriptionList.begin();

  if(descriptionList.size() <= idx)
    it = descriptionList.end();
  else
    for(int i=0 ; i < idx; i++)
      it++;

  return (*it);
}

void Item::drawImage(int posX, int posY){

  if (!imageIsVisible)
    return;

  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();

  driver->draw2DImage(TextureManager::GetTexture(imageName), 
                      core::position2d<s32>(posX, posY)
                      );

}