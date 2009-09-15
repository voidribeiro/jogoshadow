#include "HeroModel.h"

HeroModel::HeroModel() : Model(){

}

/*
HeroModel::HeroModel(const HeroModel& hero) : Model(){
  this = hero;
}
*/

HeroModel::HeroModel(const int id, const int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node) 
: Model(id, modelType, mesh)
{
  this->node = node;
}

HeroModel::HeroModel(const int id, const int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture)
: Model(id, modelType, mesh)
{
  video::SMaterial material;

	material.setTexture(0, texture);
	material.Lighting = false;

  this->node = node;
  this->node->getMaterial(0) = material;
}


HeroModel::~HeroModel(){
  if(node)
    node->drop();
}