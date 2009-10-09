#ifndef _LOADER_H_
#define _LOADER_H_

extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include <string>

#include "Script.h"
#include "Factory.h"

#include <list>

using namespace std;

class Loader{
  private:
    std::string executablePath;
    Script luaScript;

    std::list<lua_CFunction> functions;

  public:
    explicit Loader(std::string appPath);
    virtual ~Loader();
    //Register funcions to be used in the Lua Loader
    void RegisterFunction(lua_CFunction function);
    void LoadLevel(char* level);
};

#endif