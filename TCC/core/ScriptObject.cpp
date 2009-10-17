#include "ScriptObject.h"

ScriptObject::ScriptObject(){
}

ScriptObject::~ScriptObject(){
}

void ScriptObject::Execute(const char* scriptToExecute, const char* functionToExecute){
  luaScript.startScript((char*)scriptToExecute);
  for (std::list<lua_CFunction>::iterator it = functions.begin(); it!=functions.end(); it++)
    luaScript.registerFunction(*it);
  luaScript.callFunction((char*)functionToExecute,0,0,0,0);
  luaScript.endScript();
}

void ScriptObject::RegisterFunction(lua_CFunction function){
  functions.push_back(function);
}