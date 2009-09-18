#ifndef _HEROMODEL_H_
#define _HEROMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;
using namespace video;

class HeroModel : public Model{
  private:
    IAnimatedMesh* mesh;
    IAnimatedMeshSceneNode* node;

  public:
    explicit HeroModel();
//    explicit HeroModel(HeroModel& hero);
    explicit HeroModel(const int id, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node);
    explicit HeroModel(const int id, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture);
    virtual ~HeroModel();

    IAnimatedMesh*          getMesh() { return mesh; }
    IAnimatedMeshSceneNode* getNode() { return node; }
};

#endif