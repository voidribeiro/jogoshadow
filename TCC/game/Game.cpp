#include "Game.h"

Game::Game(std::string _path):path(_path), scope(1){

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

void Game::SetInventoryBackground(const std::string background){
  inventory.setBackground(background);
}

void Game::DisplayInventory(const bool visible){
  inventory.setVisible(visible);
}

void Game::AddToInventory(const std::string objName, GameObject* obj){
  inventory.add(objName, obj);
}

void Game::RemoveFromInventory(const std::string objName){
  inventory.remove(objName);
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
  game->SetScope( (int) lua_tonumber(L,1) );
  return 2;
}  

int GameBinder::bnd_PickNearestInteract(lua_State* L){
  LuaBinder binder(L);
  float nearstObjDist = -1;
  ComponentInteract* compInteract = NULL;

  //Check the objects searching for the nearst object
  std::map<std::string,GameObject*>::iterator it; 
  for (it = GameObjectMap::gameObjectMap.begin(); 
    it != GameObjectMap::gameObjectMap.end(); it++){
      if ((it->second) != NULL){
        ComponentSelector* selector = (ComponentSelector*)it->second->GetComponent(CSELECTOR);
        ComponentInteract* interact = (ComponentInteract*)it->second->GetComponent(CINTERACT);
        //If isnear and has interect. Keep the reference.
        if ((selector != NULL) && (interact != NULL)){
          float currentObjDist = selector->GetDistanceFromMouse(DeviceManager::eventListener->GetMouseState().pos);
          if ((nearstObjDist < 0) || ((currentObjDist >=0) && (currentObjDist<nearstObjDist))){
            nearstObjDist = currentObjDist;
            compInteract = interact;
          }
        }
      }
  }

  if (nearstObjDist == -1){
    return 0;
  }
  binder.pushusertype(compInteract,"ComponentInteract");
  return 1;
}

int GameBinder::bnd_SetInventoryBackground(lua_State* L){
  LuaBinder binder(L);
  game->SetInventoryBackground( lua_tostring(L,1) );
  return 0;
}

int GameBinder::bnd_DisplayInventory(lua_State* L){
  LuaBinder binder(L);
  game->DisplayInventory( (lua_toboolean(L,1) != 0) );
  return 0;
}

int GameBinder::bnd_AddToInventory(lua_State* L){
  LuaBinder binder(L);

  std::string objName = lua_tostring(L,1);
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");

  game->AddToInventory(objName, gameObject );
  return 0;
}

int GameBinder::bnd_RemoveFromInventory(lua_State* L){
  LuaBinder binder(L);
  game->RemoveFromInventory( lua_tostring(L,1) );
  return 0;
}