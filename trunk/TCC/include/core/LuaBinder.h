#ifndef _LUABINDER_H_
#define _LUABINDER_H_

extern "C" {
  #include "lua.h" 
  #include "lauxlib.h" 
}

class LuaBinder
{
  private:
    lua_State* L;

  public:
    explicit LuaBinder (lua_State* L): L(L){ }
 
    void pushnumber (double n);
    double checknumber (int index);

    void pushstring (const char* s);
    const char* checkstring (int index);
  
    void init (const char* tname, const char* bname, 
	  const luaL_reg *flist, int (*destroy) (lua_State*)); 

    void pushusertype (void* udata, char* tname);

    void *checkusertype (int index, const char *tname);
};


#endif