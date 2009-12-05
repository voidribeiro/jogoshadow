#ifndef _COMPONENTDIALOG_H_
#define _COMPONENTDIALOG_H_

#include "AbstractComponent.h"
#include "TextureManager.h"
#include <map>
#include <string>

using namespace irr;
using namespace gui;

class ComponentDialog : public AbstractComponent{
/*
  private:
    std::string filename;
*/
  public:
    explicit ComponentDialog();
    virtual ~ComponentDialog();
    virtual void Update(){};
    virtual void Draw();
    void Say( wchar_t* message );
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