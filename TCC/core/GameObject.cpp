#include "GameObject.h"

GameObject::GameObject(std::string _name):name(_name){
  irr::scene::ISceneManager* sceneManager = DeviceManager::GetDevice()->getSceneManager();
  sceneNode = sceneManager->addEmptySceneNode();
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
  if (sceneNode)
    sceneNode->remove();
  sceneNode = NULL;
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

AbstractComponent* GameObject::GetComponent(const char* componentTypeName){
  list<AbstractComponent*>::iterator it;
  for (it = componentList.begin(); it != componentList.end(); it++)
    if (((*it) != NULL) && (strcmp((*it)->GetTypeName(),componentTypeName)))
        return (*it);
  return NULL;
}

AbstractComponent* GameObject::GetComponentByIndex(int index){
  return NULL;
}

core::vector3df GameObject::GetPosition(){
  return sceneNode->getPosition();
}

void GameObject::SetPosition(const core::vector3df &newpos){
  sceneNode->setPosition(newpos);
}

void GameObject::AddChildNode(scene::ISceneNode* childNode){
  sceneNode->addChild(childNode);
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

int GameObjectBinder::bnd_InstPersistent(lua_State* L){
  LuaBinder binder(L);
  GameObject* gameObject = new GameObject(lua_tostring(L,1));
  //Add object to the map - maybe we have to change this
  GameObjectMap::Add(lua_tostring(L,1),gameObject, true);
  binder.pushusertype(gameObject,"GameObject");
  return 1; 
}
 
int GameObjectBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  GameObject* gameObject = new GameObject(lua_tostring(L,1));
  //Add object to the map - maybe we have to change this
  GameObjectMap::Add(lua_tostring(L,1),gameObject, false);
  binder.pushusertype(gameObject,"GameObject");
  return 1; 
}

int GameObjectBinder::bnd_SetPosition(lua_State* L){
  LuaBinder binder(L);
  GameObject* gameObject  = (GameObject*) binder.checkusertype(1,"GameObject");
  float posX = (float) lua_tonumber(L, 2);
  float posY = (float) lua_tonumber(L, 3);
  float posZ = (float) lua_tonumber(L, 4);
  gameObject->SetPosition(core::vector3df(posX, posY, posZ));
  return 1;
}

int GameObjectBinder::bnd_ReBinder(lua_State* L){
  LuaBinder binder(L);
  GameObject* gameObject = (GameObject*)lua_touserdata(L,1);
  binder.pushusertype(gameObject,"GameObject");  
  return 1; 
} 
 
//---------------------------------------------------------

std::map<std::string,GameObject*> GameObjectMap::gameObjectMap;
std::map<std::string,GameObject*> GameObjectMap::gameObjectPersistentMap;
std::string GameObjectMap::levelToLoad;

void GameObjectMap::Add(std::string objName, GameObject* gObj, bool persistent){
  if (persistent){
    if (GameObjectMap::gameObjectPersistentMap[objName] != NULL)
      std::cout<<"Sobrescrevendo objeto de nome "<<objName.c_str()<<std::endl;
    GameObjectMap::gameObjectPersistentMap[objName] = gObj;
    return;
  }

  if (GameObjectMap::gameObjectMap[objName] != NULL)
    std::cout<<"Sobrescrevendo objeto de nome "<<objName.c_str()<<std::endl;
  GameObjectMap::gameObjectMap[objName] = gObj;
}

void GameObjectMap::Clear(bool persistent){
  if (persistent){
    map<std::string,GameObject*>::iterator it;
    for (it = gameObjectPersistentMap.begin(); 
      it != gameObjectPersistentMap.end(); it++){
      if ((it->second) != NULL){
        delete (it->second);
        it->second = NULL;
      }
    }
    gameObjectMap.clear();
    return;
  }

  map<std::string,GameObject*>::iterator it;
  for (it = gameObjectMap.begin(); it != gameObjectMap.end(); it++){
    if ((it->second) != NULL){
      delete (it->second);
      it->second = NULL;
    }
  }
  gameObjectMap.clear();
}

void GameObjectMap::Update(){
  map<std::string,GameObject*>::iterator it;
  for (it = gameObjectPersistentMap.begin(); 
    it != gameObjectPersistentMap.end(); it++){
    if ((it->second) != NULL)
      (it->second)->Update();
  }

  for (it = gameObjectMap.begin(); it != gameObjectMap.end(); it++){
    if ((it->second) != NULL)
      (it->second)->Update();
  }
}

void GameObjectMap::Draw(){
  map<std::string,GameObject*>::iterator it;

  for (it = gameObjectMap.begin(); it != gameObjectMap.end(); it++)
    if ((it->second) != NULL)
      (it->second)->Draw();
  
  for (it = gameObjectPersistentMap.begin(); 
    it != gameObjectPersistentMap.end(); it++)
      if ((it->second) != NULL)
        (it->second)->Draw();
}

GameObject* GameObjectMap::Get(std::string objName){
  GameObject* gameObject = gameObjectPersistentMap[objName];
  if (gameObject != NULL)
    return gameObject;
  return gameObjectMap[objName];
}
