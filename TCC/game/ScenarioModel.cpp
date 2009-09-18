#include "ScenarioModel.h"

ScenarioModel::ScenarioModel() : Model(){

}

ScenarioModel::ScenarioModel(const int id, IAnimatedMesh* _mesh, ISceneNode* _node, ITriangleSelector* selector) 
: Model(id, modelType), mesh(_mesh), node(_node)
{
  node->setTriangleSelector(selector);
}

ScenarioModel::~ScenarioModel(){
  selector->drop();
}