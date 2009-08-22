#ifndef __LOADER_H__
#define __LOADER_H__

extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include <string>

#include "Script.h"
#include "Factory.h"

using namespace std;

class Loader{
  private:
    string executablePath;
    Script luaScript;

    string funcName;
    lua_CFunction func;

  public:
    Loader(string appPath);
    virtual ~Loader();
    //Register funcions to be used in the Lua Loader
    void RegisterFunction(const char* functionName, lua_CFunction function);
    void LoadLevel(char* level);
};

#endif