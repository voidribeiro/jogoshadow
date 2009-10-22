#include "ComponentImage.h"

ComponentImage::ComponentImage(const std::string _filename):
  filename(_filename){
}

ComponentImage::~ComponentImage(){
}

void ComponentImage::Draw(){
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
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

int ComponentImageBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentImage* componentImage  = (ComponentImage*) binder.checkusertype(1,"ComponentImage");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentImage);
  return 1;
}