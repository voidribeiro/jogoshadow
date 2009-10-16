#include "Loader.h"

Loader::Loader(std::string appPath){
  executablePath = appPath;
}

Loader::~Loader(){
}

void Loader::LoadLevel(const char* level){
  luaScript.startScript("Scripts/loader.lua");
  for (std::list<lua_CFunction>::iterator it = functions.begin(); it!=functions.end(); it++)
    luaScript.registerFunction(*it);
  luaScript.addGlobalVar("path",(char*)executablePath.c_str());
  luaScript.addGlobalVar("level",(char*)level);
  luaScript.callFunction("startScript",0,0,0,0);
  luaScript.endScript();
}

void Loader::RegisterFunction(lua_CFunction function){
  functions.push_back(function);
}