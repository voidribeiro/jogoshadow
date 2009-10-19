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
    bool stepOver;
  public:
    explicit GameObject ();
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
    AbstractComponent* GetComponentByIndex(int index);
};

 class GameObjectBinder{
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
class GameObjectList{
  private:
    static std::list<GameObject*> gameObjectList;
    static bool stepOver;
  public:
    static void Add(GameObject* gObj);
    static void Clear();
    static void Draw();
    static void Update();
    static void StepOver();
};

#endif