#ifndef _COMPONENTDIALOG_H_
#define _COMPONENTDIALOG_H_

#include "AbstractComponent.h"
#include "TextureManager.h"
#include <map>
#include <string>
#include <stdio.h>
#include <wchar.h>
 

using namespace irr;
using namespace gui;

class ComponentDialog : public AbstractComponent{

  private:
    core::rect<s32> rectAll;
    core::rect<s32> rectText;
    
    IGUIStaticText* windowAll;
    IGUIStaticText* windowText;

    ITexture* playerImage;
    ITexture* npcImage;

    wchar_t* message;
    wchar_t* buffer;

  public:
    explicit ComponentDialog();
    virtual ~ComponentDialog();
    virtual void Update(); 
    virtual void Draw();
    
    void Say( wchar_t* _message );
    void SetPlayerImage( std::string filename );
    void SetNpcImage( std::string filename );
    void SetFont( std::string filename );
    void SetVisible(bool _visible);

    int GetType() { return CDIALOG; };
    const char* GetTypeName() { return "ComponentDialog"; };
};

class ComponentDialogBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    
    static int bnd_GetFrom(lua_State* L);

    static int bnd_Say(lua_State* L);
    static int bnd_SetPlayerImage(lua_State* L);
    static int bnd_SetNpcImage(lua_State* L);
    static int bnd_SetFont(lua_State* L);
    static int bnd_SetVisible(lua_State* L);
};

static const luaL_reg componentDialogFunctions[] = {
    {"Instantiate", ComponentDialogBinder::bnd_Instantiate},
    {"AddTo", ComponentDialogBinder::bnd_AddTo},
    {"GetFrom", ComponentDialogBinder::bnd_GetFrom},
    {"Say", ComponentDialogBinder::bnd_Say },
    {"SetPlayerImage", ComponentDialogBinder::bnd_SetPlayerImage },
    {"SetNpcImage", ComponentDialogBinder::bnd_SetNpcImage },
    {"SetFont", ComponentDialogBinder::bnd_SetFont },
    {"SetVisible", ComponentDialogBinder::bnd_SetVisible },
    {NULL, NULL}
};

#endif