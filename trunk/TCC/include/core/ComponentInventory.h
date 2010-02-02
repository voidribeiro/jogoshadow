#ifndef _COMPONENTINVENTORY_H_
#define _COMPONENTINVENTORY_H_

#include "AbstractComponent.h"
#include "Item.h"

#include <map>

//This class will substitute Image2D if is component driven
class ComponentInventory : public AbstractComponent{
  private:
    std::map <std::string, Item*> items;

    core::rect<s32> rectAll;   //rect da janela toda
    ITexture* backgroundImage; //imagem de fundo
    bool isVisible;            //se o inventário está visível, caso verdadeiro deve mudar o input para o contexto 
                               //de inventário e não interagir na tela "atrás"

  public:
    explicit ComponentInventory();
    virtual ~ComponentInventory();
    virtual void Update(){};
    virtual void Draw();
    void SetVisible(bool visible);
    
    void LoadItem(std::string itemName, bool modelIsVisible, bool isInPlayerPosession); //carrega o ítem no map "items"
    void AddItem(std::string itemName);     //adiciona o ítem ao jogador
    void RemoveItem(std::string itemName);  //remove o ítem do jogador
    void DisplayItemImage(std::string itemName, bool visible);
    void ViewItemDescription(std::string itemName);

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

    static int bnd_LoadItem  (lua_State* L);
    static int bnd_AddItem  (lua_State* L);
    static int bnd_RemoveItem  (lua_State* L);
    static int bnd_DisplayItemImage (lua_State* L);
    static int bnd_ViewItemDescription (lua_State* L);
    static int bnd_CombineItem  (lua_State* L);
};

static const luaL_reg componentInventoryFunctions[] = {
    {"Instantiate", ComponentInventoryBinder::bnd_Instantiate},
    {"AddTo", ComponentInventoryBinder::bnd_AddTo},
    {"SetVisible", ComponentInventoryBinder::bnd_SetVisible},

    {"LoadItem", ComponentInventoryBinder::bnd_AddItem},
    {"AddItem", ComponentInventoryBinder::bnd_AddItem},
    {"RemoveItem", ComponentInventoryBinder::bnd_RemoveItem},
    {"DisplayItemImage", ComponentInventoryBinder::bnd_DisplayItemImage},
    {"ViewItemDescription", ComponentInventoryBinder::bnd_ViewItemDescription},
    {"CombineItem", ComponentInventoryBinder::bnd_CombineItem},
    {NULL, NULL}
};

#endif