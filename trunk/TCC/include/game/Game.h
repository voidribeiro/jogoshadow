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
#include "Inventory.h"

using namespace std;

class ScriptObject;

class Game : private boost::noncopyable
{
  private:
    std::string path;
    Inventory* inventory;
    int scope;        //escopo de onde eu estou no jogo, para tratamento dos inputs corretamente
                      // 1 - jogo normal, 2 - diálogo, 3 - inventário

  public:
    explicit Game(std::string _path);
    virtual ~Game();
    void LoadLevel(const std::string level);
    const char* GetPath(); 
    
    int GetCurrentScope(){return scope;}
    void SetScope(const int i){ scope = i;}
};
 

class GameBinder{
  public:
    static Game* game;
    static int registerFunctions(lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_LoadLevel (lua_State* L); 
    static int bnd_GetPath(lua_State* L);
    static int bnd_GetMousePosition(lua_State* L);
    static int bnd_GetMouseClick(lua_State* L);
    static int bnd_GetCurrentScope(lua_State* L);
    static int bnd_SetScope(lua_State* L);
    //static int bnd_AddToInventory(lua_State* L);
    //static int bnd_GetFromInventory(lua_State* L);
};
 
static const luaL_reg gameFunctions[] = {
    {"LoadLevel", GameBinder::bnd_LoadLevel}, 
    {"GetPath", GameBinder::bnd_GetPath},
    {"GetMouseClick", GameBinder::bnd_GetMouseClick},
    {"GetMousePosition", GameBinder::bnd_GetMousePosition},
    {"GetCurrentScope", GameBinder::bnd_GetCurrentScope},
    {"SetScope", GameBinder::bnd_SetScope},
    //{"AddToInventory", GameBinder::bnd_AddToInventory},
    //{"GetFromInventory", GameBinder::bnd_GetFromInventory},
    {NULL, NULL}
};


#endif