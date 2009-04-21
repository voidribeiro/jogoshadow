#include "NpcModel.h"

NpcModel::NpcModel() : Model(){

}

NpcModel::NpcModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node)
: Model(id, modelType, mesh)
{
  this->node = node;
}


NpcModel::NpcModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, ITexture* texture)
: Model(id, modelType, mesh)
{
  video::SMaterial material;

	material.setTexture(0, texture);
	material.Lighting = false;

  this->node = node;
  this->node->getMaterial(0) = material;
}

NpcModel::~NpcModel(){

}