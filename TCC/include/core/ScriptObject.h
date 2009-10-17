#ifndef _SCRIPTOBJECT_H_
#define _SCRIPTOBJECT_H_

extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include <string>
#include <list>

#include "Script.h"

using namespace std;

class ScriptObject{
  private:
    Script luaScript;
    std::list<lua_CFunction> functions;
  public:
    explicit ScriptObject();
    virtual ~ScriptObject();
    //Register funcions to be used
    void RegisterFunction(lua_CFunction function);
    void Execute(const char* scriptToExecute, const char* functionToExecute);
};

#endif