#ifndef _COMPONENTDIALOG_H_
#define _COMPONENTDIALOG_H_

#include "AbstractComponent.h"
#include "TextureManager.h"
#include <map>
#include <string>

using namespace irr;
using namespace gui;

class ComponentDialog : public AbstractComponent{

  private:
    gui::IGUIStaticText* window;

  public:
    explicit ComponentDialog();
    virtual ~ComponentDialog();
    virtual void Update(); 
    virtual void Draw();
    void Say( std::string imageFile, wchar_t* message, std::string fontFile  );
    void SetVisible(bool visible);
    int GetType() { return CDIALOG; };
    const char* GetTypeName() { return "ComponentDialog"; };
};

class ComponentDialogBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    static int bnd_Say(lua_State* L);
};

static const luaL_reg componentDialogFunctions[] = {
    {"Instantiate", ComponentDialogBinder::bnd_Instantiate},
    {"AddTo", ComponentDialogBinder::bnd_AddTo},
    {"Say", ComponentDialogBinder::bnd_Say },
    {NULL, NULL}
};

#endif