#include "ComponentDialog.h"

ComponentDialog::ComponentDialog(){
}

ComponentDialog::~ComponentDialog(){
}

void ComponentDialog::Draw(){

}

void ComponentDialog::Say( wchar_t* message ){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  core::rect<s32> quadrado(0,0,800,100);
   
  env->addStaticText(message, quadrado,false, true, 0, -1, true);
}

/////////////////////////////////////////////////////////

int ComponentDialogBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentDialog",0,componentDialogFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentDialogBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentDialogBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentDialog* componentDialog = new ComponentDialog();
  binder.pushusertype(componentDialog,"ComponentDialog");
  return 1;
}

int ComponentDialogBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentDialog);

  return 1;
}

int ComponentDialogBinder::bnd_Say(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  std::string  smessage   = lua_tostring(L, 2); 
  std::wstring message    = std::wstring(smessage.begin(), smessage.end());

  componentDialog->Say((wchar_t*)message.c_str());

  return 1;
}