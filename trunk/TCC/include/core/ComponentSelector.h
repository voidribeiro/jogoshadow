#ifndef __COMPONENTSELECTOR_H__
#define __COMPONENTSELECTOR_H__

#include "AbstractComponent.h"
#include "ComponentModel.h"
#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace video;


class ComponentSelector : public AbstractComponent{
  private:
    ComponentModel* cModel;

  public:
    explicit ComponentSelector();
    virtual ~ComponentSelector();
    virtual void Update(){};
    virtual void Draw();
    int GetType() { return CSELECTOR; };
    const char* GetTypeName() { return "ComponentSelector"; };
    virtual void SetParent(GameObject* parent);
};

class ComponentSelectorBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
};

static const luaL_reg componentSelectorFunctions[] = {
    {"Instantiate", ComponentModelBinder::bnd_Instantiate},
    {"AddTo", ComponentModelBinder::bnd_AddTo},
    {NULL, NULL}
};

#endif