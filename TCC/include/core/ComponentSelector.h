#ifndef __COMPONENTSELECTOR_H__
#define __COMPONENTSELECTOR_H__

#include "AbstractComponent.h"
#include "ComponentModel.h"
#include "DeviceManager.h"
#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace video;


class ComponentSelector : public AbstractComponent{
  private:

    scene::ITriangleSelector* selector;
    void CreateSelector();

  public:
    explicit ComponentSelector();
    virtual ~ComponentSelector();
    virtual void Update(){};
    virtual void Draw();
    int GetType() { return CSELECTOR; };
    const char* GetTypeName() { return "ComponentSelector"; };
    virtual void SetParent(GameObject* parent);
    void CheckSelector();
    float GetDistanceFromMouse(irr::core::position2d<s32> mousePosition);
    irr::core::vector3df GetCollisionPoint(irr::core::position2d<s32> mousePosition);
};

class ComponentSelectorBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    static int bnd_GetCollisionPoint (lua_State* L);
    static int bnd_GetFrom (lua_State* L);
};

static const luaL_reg componentSelectorFunctions[] = {
    {"Instantiate", ComponentSelectorBinder::bnd_Instantiate},
    {"AddTo", ComponentSelectorBinder::bnd_AddTo},
    {"GetCollisionPoint", ComponentSelectorBinder::bnd_GetCollisionPoint},
    {"GetFrom", ComponentSelectorBinder::bnd_GetFrom},
    {NULL, NULL}
};

#endif