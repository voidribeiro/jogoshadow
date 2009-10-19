#include "Game.h"

Game::Game(GameManager* _gameManager):gameManager(_gameManager){
}

Game::~Game(){
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
//  Game* game = (Game*) binder.checkusertype(1,"Game");

  return 1;
}