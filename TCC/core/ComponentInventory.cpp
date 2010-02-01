#include "ComponentInventory.h"

ComponentInventory::ComponentInventory(){

}

ComponentInventory::~ComponentInventory(){

}

void ComponentInventory::Draw(){
}

void ComponentInventory::SetVisible(bool visible){
  isVisible = visible;
}

void ComponentInventory::LoadItem(std::string itemName, bool modelIsVisible, bool isInPlayerPosession){
  Item* item = new Item(itemName, modelIsVisible, isInPlayerPosession);
  
  items[itemName] = item;
}


void ComponentInventory::AddItem(std::string itemName){
  items[itemName]->setPlayerPosession(true);
}

void ComponentInventory::DisplayItemImage(std::string itemName, bool visible){
  items[itemName]->drawImage(0, 0);
}

void ComponentInventory::ViewItemDescription(std::string itemName){
}

void ComponentInventory::CombineItem(std::string itemName1, std::string itemName2){
}

//////////////////////////////////////////

int ComponentInventoryBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentInventory",0,componentInventoryFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentInventoryBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentInventoryBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory = new ComponentInventory();
  binder.pushusertype(componentInventory,"ComponentInventory");
  return 1;
}

int ComponentInventoryBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentInventory);
  return 1;
}

int ComponentInventoryBinder::bnd_SetVisible(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");

  //bool visible =  reinterpret_cast<bool>( lua_toboolean(L,2) );

  componentInventory->SetVisible( lua_toboolean(L,2) );
  return 1;
}

int ComponentInventoryBinder::bnd_LoadItem(lua_State* L){

  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");

  return 0;
}

int ComponentInventoryBinder::bnd_AddItem(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");

  return 0;
}

int ComponentInventoryBinder::bnd_DisplayItemImage(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");

  return 0;
}

int ComponentInventoryBinder::bnd_ViewItemDescription(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");

  return 0;
}

int ComponentInventoryBinder::bnd_CombineItem(lua_State* L){
  LuaBinder binder(L);
  ComponentInventory* componentInventory  = (ComponentInventory*) binder.checkusertype(1,"ComponentInventory");

  return 0;
}