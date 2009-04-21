#include "ScenarioModel.h"

ScenarioModel::ScenarioModel() : Model(){

}

ScenarioModel::ScenarioModel(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* node) 
: Model(id, modelType, mesh)
{
  this->node = node;
}

ScenarioModel::~ScenarioModel(){

}