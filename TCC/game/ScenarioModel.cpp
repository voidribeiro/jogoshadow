#include "ScenarioModel.h"

ScenarioModel::ScenarioModel() : Model(){

}

ScenarioModel::ScenarioModel(int id, int modelType, IAnimatedMesh* mesh, ISceneNode* node, ITriangleSelector* selector) 
: Model(id, modelType, mesh)
{
  this->node = node;
  this->selector = selector;
  this->node->setTriangleSelector(selector);
}

ScenarioModel::~ScenarioModel(){
  selector->drop();
}