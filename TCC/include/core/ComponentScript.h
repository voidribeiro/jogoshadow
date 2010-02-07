#ifndef __COMPONENTSCRIPT_H__
#define __COMPONENTSCRIPT_H__

#include "AbstractComponent.h"
#include "ScriptObject.h"

#include <string>

class ScriptObject;

class ComponentScript : public AbstractComponent{
  protected:
    ScriptObject* scriptObj;
  public:
    explicit ComponentScript(std::string script);
    virtual ~ComponentScript();
    virtual void Update();
    virtual void Draw(){};
    virtual int GetType() { return CSCRIPT; };
    virtual const char* GetTypeName() { return "ComponentScript"; };
};

class ComponentScriptBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
};

static const luaL_reg componentScriptFunctions[] = {
    {"Instantiate", ComponentScriptBinder::bnd_Instantiate},
    {"AddTo", ComponentScriptBinder::bnd_AddTo},
    {NULL, NULL}
};

#endif