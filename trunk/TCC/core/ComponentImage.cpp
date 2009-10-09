#include "ComponentImage.h"

ComponentImage::ComponentImage(GameObject* parent):AbstractComponent(parent){
}

ComponentImage::~ComponentImage(){
}

void ComponentImage::Draw(){
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();
  driver->draw2DImage(TextureManager::GetTexture(filename), core::position2d<s32>(0,0));
}
