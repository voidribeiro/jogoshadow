#ifndef _NPCMODEL_H_
#define _NPCMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;
using namespace video;

class NpcModel : public Model{
  private:
    IAnimatedMeshSceneNode* node;

    //haverá algum tipo de trinagle selector aqui? se não, esta classe é exatamente igual a classe de HeroModel

  public:
    NpcModel();
    NpcModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node);
    NpcModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture);
    ~NpcModel();
    
    irr::scene::IAnimatedMeshSceneNode* getNode() { return node; }

};

#endif