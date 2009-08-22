#ifndef __FACTORY_H__
#define __FACTORY_H__

namespace FactoryType{
  static enum FactoryEnum{
    Texture,
    Model
  };
}

extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include "LuaBinder.h"

class Factory{
  public:
    Factory();
    virtual ~Factory();
    
    int Create(int type,const char* path);
};

class FactoryBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_Destroy (lua_State* L);
    static int bnd_Create (lua_State* L);
};

static const luaL_reg factoryFunctions[] = {
    {"Instantiate", FactoryBinder::bnd_Instantiate},
    {"Create", FactoryBinder::bnd_Create},
    {NULL, NULL}
};

#endif