#include "HeroModel.h"

HeroModel::HeroModel() : Model(){

}

/*
HeroModel::HeroModel(const HeroModel *const hero) : Model(){
  this = hero;
}
*/

HeroModel::HeroModel(const int id, IAnimatedMesh* _mesh, IAnimatedMeshSceneNode* _node) 
: Model(id, 1), mesh(_mesh), node(_node){

}

HeroModel::HeroModel(const int id, IAnimatedMesh* _mesh, IAnimatedMeshSceneNode* _node, ITexture* texture)
: Model(id, 1), mesh(mesh), node(_node){
  video::SMaterial material;

	material.setTexture(0, texture);
	//material.Lighting = false;

  node->getMaterial(0) = material;
}


HeroModel::~HeroModel(){
  if (node)
    node->remove();
  node = 0;

  if (mesh)
    mesh->drop();
	mesh = 0;

}