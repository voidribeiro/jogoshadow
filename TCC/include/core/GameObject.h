#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "irrlicht.h"

#include "DeviceManager.h"
#include "AbstractComponent.h"
#include "LuaBinder.h"

#include <List>
#include <Map>
#include <iostream>
#include <string>
using namespace std;
using namespace irr;

class AbstractComponent;

class GameObject{
  private:  
    std::list<AbstractComponent*> componentList;
    bool stepOver;
    scene::ISceneNode* sceneNode;
    std::string name;
  public:
    explicit GameObject (std::string _name);
    virtual ~GameObject();
    void Update();
    void Draw();
    void AddComponent(AbstractComponent* component);
    void RemoveAllComponents();
    void RemoveComponent(int componentType);
    void RemoveComponentByIndex(int index);
    void StepOver();
    int GetComponentsCount();
    AbstractComponent* GetComponent(int componentType);
    AbstractComponent* GetComponent(const char* componentTypeName);
    AbstractComponent* GetComponentByIndex(int index);

    //Methods to acess the node
    irr::core::vector3df GetPosition();
    void SetPosition(const core::vector3df &newpos);

    void AddChildNode(scene::ISceneNode* childNode);
};

 class GameObjectBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_InstPersistent (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_SetPosition (lua_State* L);
    static int bnd_ReBinder (lua_State* L);
};

static const luaL_reg gameObjectFunctions[] = {
    {"Instantiate", GameObjectBinder::bnd_Instantiate},
    {"InstPersistent", GameObjectBinder::bnd_InstPersistent},
    {"SetPosition", GameObjectBinder::bnd_SetPosition},
    {"ReBinder", GameObjectBinder::bnd_ReBinder},
    {NULL, NULL}
}; 

//TODO - See a better way to do this list
class GameObjectMap{
  private:
    static std::map<std::string,GameObject*> gameObjectMap;
    static std::map<std::string,GameObject*> gameObjectPersistentMap;
    static bool stepOver;
  public:
    static void Add(std::string objName,GameObject* gObj, bool persisent);
    static GameObject* Get(std::string objName);
    static void Clear(bool persisent);
    static void Draw();
    static void Update();
    static void StepOver();
};

#endif