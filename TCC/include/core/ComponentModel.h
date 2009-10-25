#ifndef __COMPONENTMODEL_H__
#define __COMPONENTMODEL_H__

#include "AbstractComponent.h"
#include "TextureManager.h"
#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace video;


//This class will substitute Image2D if is component driven
class ComponentModel : public AbstractComponent{
  private:
    std::string filename;

    IAnimatedMesh* mesh;
    IAnimatedMeshSceneNode* node;

  public:
    explicit ComponentModel(const std::string filename);
    virtual ~ComponentModel();
    virtual void Update(){};
    virtual void Draw();
    int GetType() { return CMODEL; };
    void setMaterial( video::SMaterial material );
    virtual void SetParent(GameObject* parent);
};

class ComponentModelBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    static int bnd_SetTexture (lua_State* L);
};

static const luaL_reg componentModelFunctions[] = {
    {"Instantiate", ComponentModelBinder::bnd_Instantiate},
    {"AddTo", ComponentModelBinder::bnd_AddTo},
    {"SetTexture", ComponentModelBinder::bnd_SetTexture},
    {NULL, NULL}
};

#endif