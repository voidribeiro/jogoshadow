#ifndef __COMPONENTSKYBOX_H__
#define __COMPONENTSKYBOX_H__

#include "AbstractComponent.h"
#include "TextureManager.h"
#include "DeviceManager.h"

class ComponentSkybox : public AbstractComponent{
  private:
    std::string upTexture;
    std::string dnTexture;
    std::string lfTexture;
    std::string rtTexture;
    std::string ftTexture;
    std::string bkTexture;
  public:
    explicit ComponentSkybox( const std::string upTexture,
                              const std::string dnTexture,
                              const std::string lfTexture,
                              const std::string rtTexture,
                              const std::string ftTexture,
                              const std::string bkTexture);
    virtual ~ComponentSkybox();
    virtual void Update(){};
    virtual void Draw();
    int GetType() { return CSKYBOX; };
};

class ComponentSkyboxBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
};

static const luaL_reg ComponentSkyboxFunctions[] = {
    {"Instantiate", ComponentSkyboxBinder::bnd_Instantiate},
    {"AddTo", ComponentSkyboxBinder::bnd_AddTo},
    {NULL, NULL}
};

#endif