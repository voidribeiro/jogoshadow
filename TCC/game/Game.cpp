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

void Game::SetInventoryBackground(std::string background){
  inventory.setBackground(background);
}

void Game::DisplayInventory(bool visible){
  inventory.setVisible(visible);
}

void Game::DrawInventory(){
  inventory.draw();
}

int Game::IsInInventory(const std::string objName){
  return ( inventory.isInInventory(objName)? 1 : 0 );
}


void Game::AddToInventory(std::string objName){
  GameObject* obj = GameObjectMap::Get(objName);
  if (obj == NULL){
    std::cout<<"Item " << objName
      <<" is not in the object map and cannot be added to inventory."<<std::endl;
    return;
  }
  inventory.add(obj);

  //TODO - Remove this evil code!
  ComponentModel* cModel = (ComponentModel*)obj->GetComponent(CMODEL);
  if (cModel != NULL){
    delete (cModel);
    cModel = NULL;
  } 

  //This is not better than the other code.
  GameObjectMap::RemoveReference(objName);
}

void Game::RemoveFromInventory(std::string objName){
  inventory.remove(objName);
}

void Game::PlayMusic(std::string filename, bool loop){
  DeviceManager::soundDevice->play2D(filename.c_str(), loop);
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

int GameBinder::bnd_GetMouseLeft(lua_State* L){
  LuaBinder binder(L);
 
  if(DeviceManager::eventListener->GetMouseState().LeftButtonDown){
    binder.pushnumber(1);
    return 1;
  }

  binder.pushnumber(0);
  return 1;
}

int GameBinder::bnd_GetMouseRight(lua_State* L){
  LuaBinder binder(L);
 
  if(DeviceManager::eventListener->GetMouseState().RightButtonDown){
    binder.pushnumber(1);
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

  //TODO - Check if object is visible in scene
  std::list<GameObject*> objectList;
  GameObjectMap::GetGameObjectList(&objectList);
  std::list<GameObject*>::iterator it;

  //Check the objects searching for the nearst object
  for (it = objectList.begin(); 
    it != objectList.end(); it++){
      if ((*it) != NULL){
        ComponentSelector* selector = (ComponentSelector*)(*it)->GetComponent(CSELECTOR);
        ComponentInteract* interact = (ComponentInteract*)(*it)->GetComponent(CINTERACT);
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

int GameBinder::bnd_DrawInventory(lua_State* L){
  LuaBinder binder(L);
  game->DrawInventory();
  return 0;
}

int GameBinder::bnd_IsInInventory(lua_State* L){
  LuaBinder binder(L); 
 
  binder.pushnumber( game->IsInInventory( lua_tostring(L,1) ) );

  return 1;   
}   

 
int GameBinder::bnd_AddToInventory(lua_State* L){
  LuaBinder binder(L);
 
  game->AddToInventory( lua_tostring(L,1) );

  return 0;
}

int GameBinder::bnd_RemoveFromInventory(lua_State* L){
  LuaBinder binder(L);
  game->RemoveFromInventory( lua_tostring(L,1) );
  return 0;
}

int GameBinder::bnd_PlayMusic(lua_State* L){
  LuaBinder binder(L);
  game->PlayMusic( lua_tostring(L,1), (lua_toboolean(L,2) != 0) );

  return 0;
}  

int GameBinder::bnd_GetObject(lua_State* L){
  LuaBinder binder(L); 
 
  //tem que retornar nulo caso não exista!
  binder.pushusertype(GameObjectMap::Get(lua_tostring(L,1)), "GameObject" );

  return 1;
}  