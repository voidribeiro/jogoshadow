#include "HeroModel.h"

HeroModel::HeroModel() : Model(){

}

HeroModel::HeroModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node) 
: Model(id, modelType, mesh)
{
  this->node = node;
}

HeroModel::HeroModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture)
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