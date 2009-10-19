#ifndef _SCRIPTOBJECT_H_
#define _SCRIPTOBJECT_H_

extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include <string>

#include "Script.h"
#include "GameObject.h"
#include "ComponentImage.h"
#include "ComponentTimer.h"

using namespace std;

class ScriptObject{
  protected:
    Script luaScript;
  public:
    explicit ScriptObject(const char* scriptToExecute);
    virtual ~ScriptObject();
    void Execute(const char* functionToExecute);
};

#endif