#include "Game.h"

Game::Game(std::string _path):path(_path){
}

Game::~Game(){
}

void Game::LoadLevel(std::string level){
  //Remove the objects from another scene
  GameObjectMap::Clear(false);
  ScriptObject loader("Scripts/loader.lua");
  loader.AddGlobalVar("path", (char*)path.c_str());
  loader.AddGlobalVar("level",(char*)level.c_str());
  loader.Execute("startScript");
}

const char* Game::GetPath(){
  return path.c_str();
}

/****************************************************/
//Binder to Lua

Game* GameBinder::game;

int GameBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("Game",0,gameFunctions, bnd_DontDestroy);
  return 0;
}

//TODO - XXX[Rafael] Chuncho master
int GameBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}

int GameBinder::bnd_LoadLevel(lua_State* L){
  LuaBinder binder(L);
  GameObjectMap::levelToLoad = lua_tostring(L,1);
  return 1;
} 

int GameBinder::bnd_GetPath(lua_State* L){
  LuaBinder binder(L);
  binder.pushstring(game->GetPath());
  return 1; 
} 

int GameBinder::bnd_GetMouseClick(lua_State* L){
  LuaBinder binder(L);

  // 0 = nada, 1 = esquerda, 2 = direita
  if(DeviceManager::eventListener->GetMouseState().LeftButtonDown){
    binder.pushnumber(1);
    return 1;
  }

  if(DeviceManager::eventListener->GetMouseState().RightButtonDown){
    binder.pushnumber(2);
    return 1;
  }

  binder.pushnumber(0);
  return 1;

}

int GameBinder::bnd_GetMousePosition(lua_State* L){
  LuaBinder binder(L);
  binder.pushnumber(DeviceManager::eventListener->GetMouseState().pos.X);
  binder.pushnumber(DeviceManager::eventListener->GetMouseState().pos.Y);
  return 2;
}  

int GameBinder::bnd_GetCurrentScope(lua_State* L){
  LuaBinder binder(L);
  binder.pushnumber(game->GetCurrentScope());
  return 2;
}  

int GameBinder::bnd_SetScope(lua_State* L){
  LuaBinder binder(L);
  game->SetScope( lua_tonumber(L,1) );
  return 2;
}  