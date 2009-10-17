#include "ComponentTimer.h"

ComponentTimer::ComponentTimer(int _timeOut, std::string _script, std::string _function):
scriptToExec(_script),functionToExec(_function){
  int timeStart = DeviceManager::getInstance()->getDevice()->getTimer()->getTime();
  timeOut = timeStart + _timeOut;
}

ComponentTimer::~ComponentTimer(){
}

#include <iostream>

void ComponentTimer::Update(){
  if (DeviceManager::getInstance()->getDevice()->getTimer()->getTime()>timeOut){
    std::cout << "Change me for the timer function" << std::endl;
  }
}


/////////////////////////////////////////////////////////

int ComponentTimerBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentTimer",0,componentTimerFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentTimerBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentTimerBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentTimer* componentTimer = new ComponentTimer(lua_tointeger(L,1),
    lua_tostring(L,2),lua_tostring(L,3));
  binder.pushusertype(componentTimer,"ComponentTimer");
  return 1;
}

int ComponentTimerBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentTimer* componentTimer  = (ComponentTimer*) binder.checkusertype(1,"ComponentTimer");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentTimer);
  return 1;
}