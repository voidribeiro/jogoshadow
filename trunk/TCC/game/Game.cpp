#include "Game.h"

Game::Game(std::string _path):path(_path){
}

Game::~Game(){
}

void Game::LoadLevel(std::string level){
  //Remove the objects from another scene
  GameObjectList::Clear();
  ScriptObject loader("Scripts/loader.lua");
  loader.AddGlobalVar("path", (char*)path.c_str());
  loader.AddGlobalVar("level",(char*)level.c_str());
  loader.Execute("startScript");
  //Turn to step the first iteration after update list
  GameObjectList::StepOver();
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

int GameBinder::bnd_GetInstance(lua_State* L){
  LuaBinder binder(L);
  binder.pushusertype(game,"Game");
  return 1;
}

int GameBinder::bnd_LoadLevel(lua_State* L){
  LuaBinder binder(L);
  Game* game = (Game*) binder.checkusertype(1,"Game");
  game->LoadLevel(lua_tostring(L,2));
  return 1;
}