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
#include "ScriptObject.h"
#include "GameObject.h"

using namespace std;

class ScriptObject;

class Game : private boost::noncopyable
{
  private:
    std::string path;
  public:
    explicit Game(std::string _path);
    virtual ~Game();
    void LoadLevel(std::string level);
    const char* GetPath(); 
};
 

class GameBinder{
  public:
    static Game* game;
    static int registerFunctions(lua_State* L);
    static int bnd_GetInstance (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_LoadLevel (lua_State* L);
    static int bnd_GetPath(lua_State* L);
};

static const luaL_reg gameFunctions[] = {
    {"GetInstance", GameBinder::bnd_GetInstance},
    {"LoadLevel", GameBinder::bnd_LoadLevel},
    {"GetPath", GameBinder::bnd_GetPath},
    {NULL, NULL}
};


#endif