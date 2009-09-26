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

#include <map>
#include "ModelManager.h"
#include "LuaBinder.h"
#include "noncopyable.hpp"

using namespace std;

class Factory : private boost::noncopyable
{
  private:
    ModelManager* modelFactory;
  
  public:
    explicit Factory();
    virtual ~Factory();
    
    void setModelFactory(ModelManager* factory);

    int Create(int type,const char* path);
    int pushAction(int type, const char* path);
};

class FactoryBinder{
  public:
    static Factory* factory;
    static int registerFunctions(lua_State* L);
    //static int bnd_Instantiate (lua_State* L);
    static int bnd_GetInstance (lua_State* L);
    //static int bnd_Destroy (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_Create (lua_State* L);
};

static const luaL_reg factoryFunctions[] = {
    //{"Instantiate", FactoryBinder::bnd_Instantiate},
    {"GetInstance", FactoryBinder::bnd_GetInstance},
    {"Create", FactoryBinder::bnd_Create},
    {NULL, NULL}
};

#endif