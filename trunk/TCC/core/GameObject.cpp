#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

//TODO - Implement all of this

void GameObject::Draw(){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++)
    if ((*it) != NULL)
      (*it)->Draw();
} 

void GameObject::AddComponent(AbstractComponent* component){
  component->SetParent(this);
  componentList.push_back(component);
}

void GameObject::RemoveComponent(int componentType){
}

void GameObject::RemoveComponentByIndex(int index){
}

void GameObject::RemoveAllComponents(){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++)
    if ((*it) != NULL)
      delete (*it);
}

int GameObject::GetComponentsCount(){
  return componentList.size();
}
 
AbstractComponent* GameObject::GetComponent(int componentType){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++)
    if (((*it) != NULL) && ((*it)->GetType() == componentType))
        return (*it);
  return NULL;
}

AbstractComponent* GameObject::GetComponentByIndex(int index){
  return NULL;
}

/////////////////////////////////////////////////////////

int GameObjectBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("GameObject",0,gameObjectFunctions, bnd_DontDestroy);
  return 0;
}

int GameObjectBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int GameObjectBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  GameObject* gameObject = new GameObject();
  //Add object to the list - maybe we have to change this
  gameObjectList.push_back(gameObject);
  binder.pushusertype(gameObject,"GameObject");
  return 1;
}
#include "ComponentImage.h"

int GameObjectBinder::bnd_AddComponent(lua_State* L){
  LuaBinder binder(L);
  GameObject* gameObject = (GameObject*) binder.checkusertype(1,"GameObject");
  ComponentImage* component = (ComponentImage*) binder.checkusertype(2,"ComponentImage");
  //gameObject->AddComponent((AbstractComponent*)lua_touserdata(L,1));
  //std::cout<<"AAAAAAAAAAAAAAAAAAAAAAAA"<<((AbstractComponent*)lua_tointeger(L,1))->GetType();
  return 1;
}