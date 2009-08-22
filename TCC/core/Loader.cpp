#include "Loader.h"

Loader::Loader(string appPath){
  executablePath = appPath;
}

Loader::~Loader(){
}

void Loader::LoadLevel(char* level){
  luaScript.startScript("Scripts/loader.lua");
  luaScript.registerFunction(func);
  luaScript.addGlobalVar("path",(char*)executablePath.c_str());
  luaScript.addGlobalVar("level",level);
  luaScript.callFunction("startScript",0,0,0,0);
  luaScript.endScript();
}

void Loader::RegisterFunction(lua_CFunction function){
  func = function;
}