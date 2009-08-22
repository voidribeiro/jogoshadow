#include "Factory.h"

Factory::~Factory(){
}

int Factory::Create(int type, char *path){
  return type;
}

int Factory::Create(lua_State *luaState){
  //Get the number of arguments
  int argc = lua_gettop(luaState);

  //Gets the type of the factory
  int factoryType = lua_tonumber(luaState, 1);
  
  //Calls the function and return to lua
  lua_pushnumber(luaState, Create(factoryType, ""));

  //Sets the number of arguments returned
  return 1;
}