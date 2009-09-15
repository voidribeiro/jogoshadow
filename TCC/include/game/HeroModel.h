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
    explicit HeroModel();
//    explicit HeroModel(const HeroModel& hero);
    explicit HeroModel(const int id, const int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node);
    explicit HeroModel(const int id, const int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture);
    virtual ~HeroModel();
    
    IAnimatedMeshSceneNode* getNode() { return node; }

};

#endif