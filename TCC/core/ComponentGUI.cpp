#include "ComponentGUI.h"

ComponentGUI::ComponentGUI(){

}

ComponentGUI::~ComponentGUI(){

}

void ComponentGUI::Draw(){

}

void ComponentGUI::addMessageBox(wchar_t* title, wchar_t* message, bool modal){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  env->addMessageBox(title, message, true);
}

/////////////////////////////////////////////////////////

int ComponentGUIBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentGUI",0,componentGUIFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentGUIBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentGUIBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI = new ComponentGUI();
  binder.pushusertype(componentGUI,"ComponentGUI");
  return 1;
}

int ComponentGUIBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentGUI);
  return 1;
}

int ComponentGUIBinder::bnd_AddMessageBox(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");

  //está fixo porque eu não sei converter de string pra wchar_t*
  componentGUI->addMessageBox(L"TESTE", L"TESTE!", true);

  return 1;
}
