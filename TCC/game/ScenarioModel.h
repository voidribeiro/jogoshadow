#ifndef _SCENARIOMODEL_H_
#define _SCENARIOMODEL_H_

#include "Model.h"

class ScenarioModel : public Model{
  private:
    irr::scene::ISceneNode* node;
    
    // como a gente vai tratar a movimentação na malha?
    // isto ficaria aqui ou seria tratada num classe controller da vida?
    
    // irr::scene::IAnimatedMesh* navMesh;

  public:
    ScenarioModel();
    ScenarioModel(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* node);
    ~ScenarioModel();
    
    irr::scene::ISceneNode* getNode() { return node; }

};

#endif