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
#include "GameObject.h"
#include "ComponentImage.h"
#include "ComponentTimer.h"

using namespace std;

class ScriptObject{
  protected:
    Script luaScript;
    std::list<lua_CFunction> functions;
    //Register funcions to be used
    //This now will be done in the constructor
    void RegisterFunction(lua_CFunction function);
  public:
    explicit ScriptObject();
    virtual ~ScriptObject();
    void Execute(const char* scriptToExecute, const char* functionToExecute);
};

#endif