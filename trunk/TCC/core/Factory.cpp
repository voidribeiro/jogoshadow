#include "Factory.h"

Factory::Factory(){
}

Factory::~Factory(){
}



int Factory::Create(int type,const char *path){
  modelFactory->pushModel(path, type);
  return type;
}

void Factory::setModelFactory(ModelManager* factory){
  modelFactory = factory;  
}

int Factory::pushAction(int type, const char *path){
  std::map <int, const char*>::iterator it = actions.end();
  actions.insert(it, pair<int, const char*>( type, path ) );
  return type;
}

/****************************************************/
//Binder to Lua

void FactoryBinder::setModelFactory(ModelManager* factory){
  modelFactory = factory;  
}

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
  binder.pushnumber(factory->pushAction(lua_tointeger(L,2),lua_tostring(L,3)));
  return 1;
}