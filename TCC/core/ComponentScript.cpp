#include "ComponentScript.h"

ComponentScript::ComponentScript(std::string script){
  scriptObj = new ScriptObject(script.c_str());
  scriptObj->AddGlobalUserVar("parentObject",parent);
  scriptObj->Execute("start");
}

ComponentScript::~ComponentScript(){
  scriptObj->Execute("destroy");
  delete scriptObj;
}

void ComponentScript::Update(){
  scriptObj->Execute("update");
}

/////////////////////////////////////////////////////////

int ComponentScriptBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentScript",0,componentScriptFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentScriptBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentScriptBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentScript* componentScript = new ComponentScript(lua_tostring(L,1));
  binder.pushusertype(componentScript,"ComponentScript");
  return 1;
}

int ComponentScriptBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentScript* componentScript  = (ComponentScript*) binder.checkusertype(1,"ComponentScript");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentScript);
  return 1;
}