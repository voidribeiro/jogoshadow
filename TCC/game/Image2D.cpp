#include "Image2D.h"

Image2D::Image2D(const std::string _filename, TextureManager* _textureManager):
  filename(_filename),
  textureManager(_textureManager){
  
}

Image2D::~Image2D(){
}

void Image2D::draw(){
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();
  driver->draw2DImage(textureManager->GetTexture(filename), core::position2d<s32>(0,0));
}