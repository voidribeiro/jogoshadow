#include "Loader.h"

Loader::Loader(std::string appPath):ScriptObject("Scripts/loader.lua"){
  executablePath = appPath;
}

Loader::~Loader(){
}

void Loader::LoadLevel(const char* level){
  luaScript.addGlobalVar("path",(char*)executablePath.c_str());
  luaScript.addGlobalVar("level",(char*)level);
  luaScript.callFunction("startScript",0,0,0,0);
}