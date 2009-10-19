#ifndef __COMPONENTIMAGE_H__
#define __COMPONENTIMAGE_H__

#include "AbstractComponent.h"
#include "TextureManager.h"

//This class will substitute Image2D if is component driven
class ComponentImage : public AbstractComponent{
  private:
    std::string filename;
  public:
    explicit ComponentImage(const std::string filename);
    virtual ~ComponentImage();
    virtual void Update(){};
    virtual void Draw();
    int GetType() { return CIMAGE; };
};

class ComponentImageBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
};

static const luaL_reg componentImageFunctions[] = {
    {"Instantiate", ComponentImageBinder::bnd_Instantiate},
    {"AddTo", ComponentImageBinder::bnd_AddTo},
    {NULL, NULL}
};

#endif