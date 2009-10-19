#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::~GameObject(){
  while (componentList.size() != 0){
    AbstractComponent* c = (*componentList.begin());
    componentList.pop_front();
    if (c != NULL){
      delete c;
      c = NULL;
    }
  }
}

//TODO - Implement all of this

void GameObject::Update(){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++){
    if ((*it) != NULL)
      (*it)->Update();
    //TODO - resolve this problem. This happen due a object list update
    if (componentList.empty()){
      return;
    }
    if (stepOver)
      return;
  }
} 

void GameObject::Draw(){
  list<AbstractComponent*>::iterator it;
  if (!stepOver)
    for (it = componentList.begin(); it != componentList.end(); it++)
      if ((*it) != NULL)
        (*it)->Draw();
  stepOver = false;
}

void GameObject::StepOver(){
  stepOver = true;
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
    if ((*it) != NULL){
      delete (*it);
      (*it) = NULL;
    }
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
  GameObjectList::Add(gameObject);
  binder.pushusertype(gameObject,"GameObject");
  return 1;
}


//---------------------------------------------------------

std::list<GameObject*> GameObjectList::gameObjectList;
bool GameObjectList::stepOver;

void GameObjectList::Add(GameObject* gObj){
  GameObjectList::gameObjectList.push_back(gObj);
}

void GameObjectList::Clear(){
  while (gameObjectList.size() > 0){
    GameObject* gObj = (*gameObjectList.begin());
    gameObjectList.pop_front();
    if (gObj != NULL){
      delete gObj;
      gObj = NULL;
    }
  }
  StepOver();
}

void GameObjectList::Update(){
  list<GameObject*>::iterator it;
  for (it = gameObjectList.begin(); it != gameObjectList.end(); it++){
    if ((*it) != NULL)
      (*it)->Update();
    //Only update require stepOver that is why don't start with a stepOver
    if (stepOver)
      return;
  }
}

void GameObjectList::Draw(){
  list<GameObject*>::iterator it;
  //If update required stepOver will wait one drawcall before draw again
  if (!stepOver)
    for (it = gameObjectList.begin(); it != gameObjectList.end(); it++)
      if ((*it) != NULL)
        (*it)->Draw();

  stepOver = false;
}

void GameObjectList::StepOver(){
  stepOver = true;
}