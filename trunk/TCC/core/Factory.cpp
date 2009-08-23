#include "Factory.h"

Factory::Factory(){
}

Factory::~Factory(){
}

int Factory::Create(int type,const char *path){
  return type;
}

/****************************************************/
//Binder to Lua

int FactoryBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("Factory",0,factoryFunctions,FactoryBinder::bnd_Destroy);
  return 0;
}

int FactoryBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  Factory* factory = new Factory();
  binder.pushusertype(factory,"Factory");
  return 1;
}

int FactoryBinder::bnd_Destroy(lua_State* L){
  LuaBinder binder(L);
  Factory* factory = (Factory*) binder.checkusertype(1,"Factory");
  delete factory;
  return 0;
}

int FactoryBinder::bnd_Create(lua_State* L){
  LuaBinder binder(L);
  Factory* factory = (Factory*) binder.checkusertype(1,"Factory");
  binder.pushnumber(factory->Create(lua_tointeger(L,2),lua_tostring(L,3)));
  return 1;
}