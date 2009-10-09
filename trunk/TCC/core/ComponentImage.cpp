#include "ComponentImage.h"

ComponentImage::ComponentImage(const std::string _filename):
  filename(_filename){
}

ComponentImage::~ComponentImage(){
}

void ComponentImage::Draw(){
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();
  driver->draw2DImage(TextureManager::GetTexture(filename), core::position2d<s32>(0,0));
}


/////////////////////////////////////////////////////////

int ComponentImageBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentImage",0,componentImageFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentImageBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentImageBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentImage* componentImage = new ComponentImage(lua_tostring(L,1));
  binder.pushusertype(componentImage,"ComponentImage");
  return 1;
}