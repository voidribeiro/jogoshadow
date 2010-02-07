#ifndef __COMPONENTINTERACT_H__
#define __COMPONENTINTERACT_H__

#include "AbstractComponent.h"
#include "ScriptObject.h"

#include <string>

class ScriptObject;

class ComponentInteract : public AbstractComponent{
  protected:
    ScriptObject* scriptObj;
  public:
    explicit ComponentInteract(std::string script);
    virtual ~ComponentInteract();
    virtual void Update(){};
    virtual void Draw(){};
    virtual int GetType() { return CINTERACT; };
    virtual const char* GetTypeName() { return "ComponentInteract"; };
    void Interact();
    void Interact(string object);
    void Inspect();
};

class ComponentInteractBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    static int bnd_InteractWith (lua_State* L);
    static int bnd_Inspect (lua_State* L);
    static int bnd_Interact (lua_State* L);
};

static const luaL_reg componentInteractFunctions[] = {
    {"Instantiate", ComponentInteractBinder::bnd_Instantiate},
    {"AddTo", ComponentInteractBinder::bnd_AddTo},
    {"InterectWith", ComponentInteractBinder::bnd_InteractWith},
    {"Inspect", ComponentInteractBinder::bnd_Inspect},
    {"Interect", ComponentInteractBinder::bnd_Interact},
    {NULL, NULL}
};

#endif