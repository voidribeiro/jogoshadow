#ifndef _SCENARIOMODEL_H_
#define _SCENARIOMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;

class ScenarioModel : public Model{
  private:
    IAnimatedMesh*  mesh;
    ISceneNode*     node;
    ITriangleSelector* selector;

    // como a gente vai tratar a movimentação na malha?
    // isto ficaria aqui ou seria tratada numa classe controller da vida?

    // irr::scene::IAnimatedMesh* navMesh;


  public:
    explicit ScenarioModel();
    explicit ScenarioModel(const int id, IAnimatedMesh* mesh, ISceneNode* node, ITriangleSelector* selector);
    virtual ~ScenarioModel();

    IAnimatedMesh*      getMesh() { return mesh; }
    ISceneNode*         getNode() { return node; }
    ITriangleSelector*  getSelector() { return selector; }

};

#endif