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
    bool gameOver;
    std::string path;
    Inventory inventory;
    int scope;        //escopo de onde eu estou no jogo, para tratamento dos inputs corretamente
                      // 1 - jogo normal, 2 - diálogo, 3 - inventário

  public:
    explicit Game(std::string _path);
    virtual ~Game();
    void LoadLevel(const std::string level);
    const char* GetPath(); 
    bool IsGameOver(){return gameOver;}

    int GetCurrentScope(){return scope;}
    void SetScope(const int i){ scope = i;}

    void SetInventoryBackground(const std::string background);
    void SetInventoryButton(const std::string button);
    void DisplayInventory(const bool visible);
    void DrawInventory();
    bool IsInventoryVisible();

    int  IsInInventory(const std::string objName);
    void AddToInventory(std::string objName);
    void RemoveFromInventory(const std::string objName);
    std::string GetSelectedItem();

    void PlayMusic(const std::string filename, const bool loop);

    void End();

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
    static int bnd_GetMouseLeft(lua_State* L);
    static int bnd_GetMouseRight(lua_State* L);
    static int bnd_GetCurrentScope(lua_State* L);
    static int bnd_SetScope(lua_State* L);
    static int bnd_PickNearestInteract(lua_State* L);

    static int bnd_SetInventoryBackground(lua_State* L);
    static int bnd_DisplayInventory(lua_State* L);
    static int bnd_IsInventoryVisible(lua_State* L);
    static int bnd_DrawInventory(lua_State* L);
    static int bnd_IsInInventory(lua_State* L);
    static int bnd_AddToInventory(lua_State* L);
    static int bnd_RemoveFromInventory(lua_State* L);
    static int bnd_GetSelectedItem(lua_State* L);

    static int bnd_PlayMusic(lua_State* L);

    static int bnd_GetObject(lua_State* L);
    static int bnd_End(lua_State* L);

    static int bnd_SetCameraPosition(lua_State* L);
    static int bnd_SetCameraLookAt(lua_State* L);
};
 
static const luaL_reg gameFunctions[] = { 
    {"LoadLevel", GameBinder::bnd_LoadLevel}, 
    {"GetPath", GameBinder::bnd_GetPath},
    {"GetMouseClick", GameBinder::bnd_GetMouseClick},
    {"GetMouseLeft", GameBinder::bnd_GetMouseLeft},
    {"GetMouseRight", GameBinder::bnd_GetMouseRight},
    {"GetMousePosition", GameBinder::bnd_GetMousePosition},
    {"GetCurrentScope", GameBinder::bnd_GetCurrentScope},
    {"SetScope", GameBinder::bnd_SetScope},
    {"PickNearestInteract", GameBinder::bnd_PickNearestInteract},

    {"SetInventoryBackground", GameBinder::bnd_SetInventoryBackground},
    {"DisplayInventory", GameBinder::bnd_DisplayInventory},
    {"IsInventoryVisible", GameBinder::bnd_IsInventoryVisible},
    {"DrawInventory", GameBinder::bnd_DrawInventory},
    {"IsInInventory", GameBinder::bnd_IsInInventory},
    {"AddToInventory", GameBinder::bnd_AddToInventory},
    {"RemoveFromInventory", GameBinder::bnd_RemoveFromInventory},
    {"GetSelectedItem", GameBinder::bnd_GetSelectedItem},
    
    {"PlayMusic", GameBinder::bnd_PlayMusic},

    {"GetObject", GameBinder::bnd_GetObject},
    {"End", GameBinder::bnd_End},

    {"CameraPosition", GameBinder::bnd_SetCameraPosition},
    {"CameraLookAt", GameBinder::bnd_SetCameraLookAt},

    {NULL, NULL}
};


#endif 