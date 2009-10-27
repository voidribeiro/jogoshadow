#ifndef _COMPONENTGUI_H_
#define _COMPONENTGUI_H_

#include "AbstractComponent.h"
#include "TextureManager.h"

using namespace irr;
using namespace gui;

class ComponentGUI : public AbstractComponent{
  /*
  a princípio um componente de GUI não teria parâmetros no seu construtor
  private:
    std::string filename;
  */
  public:
    explicit ComponentGUI();
    virtual ~ComponentGUI();
    virtual void Update(){};
    virtual void Draw();
    void addMessageBox(wchar_t* title, wchar_t* message, bool modal);
    int GetType() { return CGUI; };
};

class ComponentGUIBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate  (lua_State* L);
    static int bnd_DontDestroy  (lua_State* L);
    static int bnd_AddMessageBox(lua_State* L);
    static int bnd_AddTo        (lua_State* L);
};

static const luaL_reg componentGUIFunctions[] = {
    {"Instantiate", ComponentGUIBinder::bnd_Instantiate},
    {"AddTo", ComponentGUIBinder::bnd_AddTo},
    {"AddMessageBox", ComponentGUIBinder::bnd_AddMessageBox},
    {NULL, NULL}
};

#endif