#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "AbstractComponent.h"
#include "LuaBinder.h"

#include <List>
using namespace std;

class AbstractComponent;

class GameObject{
  private:  
    std::list<AbstractComponent*> componentList;
  public:
    explicit GameObject ();
    virtual ~GameObject();
    void Draw();
    void AddComponent(AbstractComponent* component);
    void RemoveAllComponents();
    void RemoveComponent(int componentType);
    void RemoveComponentByIndex(int index);
    int GetComponentsCount();
    AbstractComponent* GetComponent(int componentType);
    AbstractComponent* GetComponentByIndex(int index);
};

static class GameObjectBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
};

static const luaL_reg gameObjectFunctions[] = {
    {"Instantiate", GameObjectBinder::bnd_Instantiate},
    {NULL, NULL}
};

//TODO - See a better way to do this list
static class GameObjectList{
  private:
    static std::list<GameObject*> gameObjectList;
  public:
    static void Add(GameObject* gObj);
    static void Draw();
};

#endif