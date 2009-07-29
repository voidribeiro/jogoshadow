#ifndef _HEROMODEL_H_
#define _HEROMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;
using namespace video;

class HeroModel : public Model{
  private:
    irr::scene::IAnimatedMeshSceneNode* node;

  public:
    HeroModel();
    HeroModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node);
    HeroModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture);
    ~HeroModel();
    
    IAnimatedMeshSceneNode* getNode() { return node; }

};

#endif