#ifndef _NPCMODEL_H_
#define _NPCMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;
using namespace video;

class NpcModel : public Model{
  private:
    IAnimatedMesh* mesh;
    IAnimatedMeshSceneNode* node;
    ITriangleSelector* selector;

  public:
    explicit NpcModel();
    explicit NpcModel(int id, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node);
    explicit NpcModel(int id, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture);
    virtual ~NpcModel();
    
    IAnimatedMesh*          getMesh() { return mesh; }
    IAnimatedMeshSceneNode* getNode() { return node; }

};

#endif