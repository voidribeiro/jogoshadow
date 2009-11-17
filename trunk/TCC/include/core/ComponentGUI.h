#ifndef _COMPONENTGUI_H_
#define _COMPONENTGUI_H_

#include "AbstractComponent.h"
#include "TextureManager.h"
#include <map>
#include <string>


using namespace irr;
using namespace gui;

class ComponentGUI : public AbstractComponent{

  private:

    std::map <std::string, IGUIElement*> elements;

  public:
    explicit ComponentGUI();
    virtual ~ComponentGUI();
    virtual void Update();
    virtual void Draw();
    void addMessageBox(wchar_t* title, wchar_t* message, bool modal);
    void addImageButton(const std::string instancename, const std::string filename, int posX, int posY);
    int GetType() { return CGUI; };
    const char* GetTypeName() { return "ComponentGUI"; };
};

class ComponentGUIBinder{
  public:
    static int registerFunctions  (lua_State* L);
    static int bnd_Instantiate    (lua_State* L);
    static int bnd_DontDestroy    (lua_State* L);
    static int bnd_AddMessageBox  (lua_State* L);
    static int bnd_AddImageButton (lua_State* L);
    static int bnd_AddTo          (lua_State* L);
    static int bnd_GetFrom        (lua_State* L);
};

static const luaL_reg componentGUIFunctions[] = {
    {"Instantiate", ComponentGUIBinder::bnd_Instantiate},
    {"AddTo", ComponentGUIBinder::bnd_AddTo},
    {"GetFrom", ComponentGUIBinder::bnd_GetFrom},
    {"AddMessageBox", ComponentGUIBinder::bnd_AddMessageBox},
    {"AddImageButton", ComponentGUIBinder::bnd_AddImageButton},
    {NULL, NULL}
};

#endif