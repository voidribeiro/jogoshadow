#include "HeroModel.h"

HeroModel::HeroModel() : Model(){

}

HeroModel::HeroModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node) 
: Model(id, modelType, mesh)
{
  this->node = node;
}

HeroModel::~HeroModel(){

}