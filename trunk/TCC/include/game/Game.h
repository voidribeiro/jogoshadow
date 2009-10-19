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
#include "GameManager.h"

using namespace std;

class Game : private boost::noncopyable
{
  private:
    GameManager* gameManager;

  public:
    explicit Game(GameManager* _gameManager);
    virtual ~Game();
};


class GameBinder{
  public:
    static Game* game;
    static int registerFunctions(lua_State* L);
    static int bnd_GetInstance (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_LoadLevel (lua_State* L);
};

static const luaL_reg gameFunctions[] = {
    {"GetInstance", GameBinder::bnd_GetInstance},
    {"LoadLevel", GameBinder::bnd_LoadLevel},
    {NULL, NULL}
};


#endif