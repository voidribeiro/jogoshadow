#ifndef _GAME_H_
#define _GAME_H_


extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
};

#include <string>
#include "LuaBinder.h"
#include "noncopyable.hpp"

using namespace std;

class Game : private boost::noncopyable
{
  private:

  public:
    explicit Game();
    virtual ~Game();

    void showImage(string handle);
    void wait(int miliseconds);
    void load(string handle); // que ele vai carregar???

};


class GameBinder{
  public:
    static Game* game;
    static int registerFunctions(lua_State* L);
    static int bnd_GetInstance (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_ShowImage (lua_State* L);
    static int bnd_Wait (lua_State* L);
    static int bnd_Load (lua_State* L);
};

static const luaL_reg gameFunctions[] = {
    {"GetInstance", GameBinder::bnd_GetInstance},
    {"ShowImage", GameBinder::bnd_ShowImage},
    {"ShowWait", GameBinder::bnd_Wait},
    {"ShowLoad", GameBinder::bnd_Load},
    {NULL, NULL}
};



#endif