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

class Factory{
  private:
    
  public:
    Factory();
    virtual ~Factory();
    //Same method but use C++
    static int Create(int type,char* path);

    //Method to be registered in lua
    static int Create(lua_State* luaState);
};

#endif