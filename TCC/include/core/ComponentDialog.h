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

    std::map <std::string, IGUIElement*> options;

    //rect da janela toda
    core::rect<s32> rectAll;

    //rect da área de texto
    core::rect<s32> rectText;

    //rect da área de opções de resposta
    core::rect<s32> rectOptions;

    IGUIStaticText* windowAll;
    IGUIStaticText* windowText;
    IGUIStaticText* windowOptions;

    ITexture* playerImage;
    ITexture* npcImage;

    //ainda não está sendo usado
    wchar_t* message;
    wchar_t* buffer;

   public:
    explicit ComponentDialog();
    virtual ~ComponentDialog();
    virtual void Update(); 
    virtual void Draw();

    void Say( const wchar_t* _message );
    void SetPlayerImage( const std::string filename );
    void SetNpcImage( const std::string filename );
    void SetFont( const std::string filename );
    void SetVisible(const bool _visible);
    
    void AddOption( const std::string instanceName, const wchar_t* buttonText, const int x1, const int y1, const int x2, const int y2 );
    void AddImageOption( const std::string instanceName, const std::string filename, const int posX, const int posY);

    bool IsButtonPressed(const std::string instanceName);
    void ClearOptions();

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

    static int bnd_AddOption(lua_State* L);
    static int bnd_AddImageOption(lua_State* L);
    static int bnd_IsButtonPressed(lua_State* L);
    static int bnd_ClearOptions(lua_State* L);

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
    {"AddOption", ComponentDialogBinder::bnd_AddOption },
    {"AddImageOption", ComponentDialogBinder::bnd_AddImageOption },
    {"IsButtonPressed", ComponentDialogBinder::bnd_IsButtonPressed},
    {"ClearOptions", ComponentDialogBinder::bnd_ClearOptions },
    {"SetPlayerImage", ComponentDialogBinder::bnd_SetPlayerImage },
    {"SetNpcImage", ComponentDialogBinder::bnd_SetNpcImage },
    {"SetFont", ComponentDialogBinder::bnd_SetFont },
    {"SetVisible", ComponentDialogBinder::bnd_SetVisible },
    {NULL, NULL}
};

#endif