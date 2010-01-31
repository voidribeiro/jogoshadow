#include "ComponentSelector.h"

ComponentSelector::ComponentSelector(){
}

ComponentSelector::~ComponentSelector(){
}

void ComponentSelector::Draw(){

}

void ComponentSelector::SetParent(GameObject* parent){
  AbstractComponent::SetParent(parent);
}

/////////////////////////////////////////////////////////

int ComponentSelectorBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentSelector",0,componentSelectorFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentSelectorBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentSelectorBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentSelector* componentSelector = new ComponentSelector();
  binder.pushusertype(componentSelector,"ComponentSelector");
  return 1;
}

int ComponentSelectorBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentSelector* componentSelector  = (ComponentSelector*) binder.checkusertype(1,"ComponentSelector");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentSelector);
  return 1;
}