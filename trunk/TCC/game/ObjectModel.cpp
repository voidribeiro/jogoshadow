#include "ObjectModel.h"

ObjectModel::ObjectModel() : Model(){

}

ObjectModel::ObjectModel(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::IMeshSceneNode* node) 
: Model(id, modelType, mesh)
{
  this->node = node;
}

ObjectModel::~ObjectModel(){

}