#include "ScriptObject.h"

ScriptObject::ScriptObject(const char* _scriptToExecute):scriptToExecute(_scriptToExecute){
  luaScript.startScript((char*)_scriptToExecute);
  luaScript.registerFunction(GameBinder::registerFunctions);
  luaScript.registerFunction(GameObjectBinder::registerFunctions);
  luaScript.registerFunction(ComponentScriptBinder::registerFunctions);
  luaScript.registerFunction(ComponentImageBinder::registerFunctions);
  luaScript.registerFunction(ComponentTimerBinder::registerFunctions);
  luaScript.registerFunction(ComponentSkyboxBinder::registerFunctions);
  luaScript.registerFunction(ComponentModelBinder::registerFunctions);
  luaScript.registerFunction(ComponentGUIBinder::registerFunctions);
  luaScript.registerFunction(ComponentDialogBinder::registerFunctions);
}
 
ScriptObject::~ScriptObject(){
  luaScript.endScript();
}

void ScriptObject::Execute(const char* functionToExecute){
  if (!luaScript.callFunction((char*)functionToExecute,0,0,0,0))
    std::cout<<"Lua Error! Script:"<<scriptToExecute<<" - Function:"<<functionToExecute<<std::endl;;
}

void ScriptObject::AddGlobalVar(const char* name, const char* value){
  luaScript.addGlobalVar((char*)name, (char*)value);
}

void ScriptObject::AddGlobalUserVar(const char* name, const void* value){
  luaScript.addGlobalUserVar((char*)name, (void*)value);
}