#ifndef _COMPONENTINVENTORY_H_
#define _COMPONENTINVENTORY_H_

#include "AbstractComponent.h"
#include "Item.h"

#include <map>

//This class will substitute Image2D if is component driven
class ComponentInventory : public AbstractComponent{
  private:
    std::map <std::string, Item*> items;

    //rect da janela toda
    core::rect<s32> rectAll;

    //imagem de fundo
    ITexture* backgroundImage;

  public:
    explicit ComponentInventory();
    virtual ~ComponentInventory();
    virtual void Update(){};
    virtual void Draw();
    void SetVisible(bool visible);
    int GetType() { return CINVENTORY; };
    const char* GetTypeName() { return "ComponentInventory"; };
};

class ComponentInventoryBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    static int bnd_SetVisible (lua_State* L);

    static int bnd_AddItem  (lua_State* L);
    static int bnd_ViewItem (lua_State* L);
    static int bnd_CombineItem  (lua_State* L);
};

static const luaL_reg componentInventoryFunctions[] = {
    {"Instantiate", ComponentInventoryBinder::bnd_Instantiate},
    {"AddTo", ComponentInventoryBinder::bnd_AddTo},
    {"SetVisible", ComponentInventoryBinder::bnd_SetVisible},

    {"AddItem", ComponentInventoryBinder::bnd_AddItem},
    {"ViewItem", ComponentInventoryBinder::bnd_ViewItem},
    {"CombineItem", ComponentInventoryBinder::bnd_CombineItem},
    {NULL, NULL}
};

#endif