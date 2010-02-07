#include "ComponentImage.h"

ComponentImage::ComponentImage(const std::string _filename):
  filename(_filename),isVisible(true){
}

ComponentImage::~ComponentImage(){
}

void ComponentImage::Draw(){
  if (!isVisible)
    return;
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  core::vector3df parentPosition = parent->GetPosition();
  driver->draw2DImage(TextureManager::GetTexture(filename), 
  core::position2d<s32>( (irr::s32)parentPosition.X, (irr::s32)parentPosition.Y));
}

void ComponentImage::SetVisible(bool visible){
  isVisible = visible;
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

int ComponentImageBinder::bnd_SetVisible(lua_State* L){
  LuaBinder binder(L);
  ComponentImage* componentImage  = (ComponentImage*) binder.checkusertype(1,"ComponentImage");
  componentImage->SetVisible( ( lua_toboolean(L,2) != 0) );
  return 1;
}