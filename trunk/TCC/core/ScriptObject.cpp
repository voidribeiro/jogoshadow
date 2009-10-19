#include "ScriptObject.h"

ScriptObject::ScriptObject(const char* scriptToExecute){
  luaScript.startScript((char*)scriptToExecute);
  luaScript.registerFunction(GameBinder::registerFunctions);
  luaScript.registerFunction(GameObjectBinder::registerFunctions);
  luaScript.registerFunction(ComponentImageBinder::registerFunctions);
  luaScript.registerFunction(ComponentTimerBinder::registerFunctions);
}

ScriptObject::~ScriptObject(){
  luaScript.endScript();
}

void ScriptObject::Execute(const char* functionToExecute){
  luaScript.callFunction((char*)functionToExecute,0,0,0,0);
}

void ScriptObject::AddGlobalVar(const char* name, const char* value){
  luaScript.addGlobalVar((char*)name, (char*)value);
}