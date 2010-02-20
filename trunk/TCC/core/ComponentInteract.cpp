#include "ComponentInteract.h"

ComponentInteract::ComponentInteract(std::string script){
  scriptObj = new ScriptObject(script.c_str());
}

void ComponentInteract::Initialize(){
  if (parent != NULL)
    scriptObj->AddGlobalVar("parentObject",parent->GetName().c_str());
  else
    std::cout<<("Error parent object cannot be null");
  scriptObj->Execute("start");
}
 
ComponentInteract::~ComponentInteract(){
  scriptObj->Execute("destroy");
  delete scriptObj;
}

void ComponentInteract::Interact(){
  scriptObj->Execute("interact");
}

void ComponentInteract::Inspect(){
  scriptObj->Execute("inspect");
}

void ComponentInteract::Interact(std::string object){
  scriptObj->AddGlobalVar("interactionObject",object.c_str());
  scriptObj->Execute("interactWith");
}

/////////////////////////////////////////////////////////

int ComponentInteractBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentInteract",0,componentInteractFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentInteractBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentInteractBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentInteract* componentInteract = new ComponentInteract(lua_tostring(L,1));
  binder.pushusertype(componentInteract,"ComponentInteract");
  return 1;
}

int ComponentInteractBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentInteract* componentInteract  = (ComponentInteract*) binder.checkusertype(1,"ComponentInteract");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentInteract);
  componentInteract->Initialize();
  return 1;
}

int ComponentInteractBinder::bnd_InteractWith (lua_State* L){
  LuaBinder binder(L);
  ComponentInteract* componentInteract  = (ComponentInteract*) binder.checkusertype(1,"ComponentInteract");
  componentInteract->Interact(lua_tostring(L,2));
  return 1;
}

int ComponentInteractBinder::bnd_Inspect (lua_State* L){
  LuaBinder binder(L); 
  ComponentInteract* componentInteract  = (ComponentInteract*) binder.checkusertype(1,"ComponentInteract");
  componentInteract->Inspect();
  return 1;
}

int ComponentInteractBinder::bnd_Interact (lua_State* L){
  LuaBinder binder(L);
  ComponentInteract* componentInteract  = (ComponentInteract*) binder.checkusertype(1,"ComponentInteract");
  componentInteract->Interact(); 
  return 1;
}