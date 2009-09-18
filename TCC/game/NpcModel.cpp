#include "NpcModel.h"

NpcModel::NpcModel() : Model(){

}

NpcModel::NpcModel(int id, IAnimatedMesh* _mesh, IAnimatedMeshSceneNode* _node)
: Model(id, 2), mesh(_mesh), node(_node){

}


NpcModel::NpcModel(int id, IAnimatedMesh* _mesh, IAnimatedMeshSceneNode* _node, ITexture* texture)
: Model(id, 2), mesh(_mesh), node(_node){
  video::SMaterial material;
  material.setTexture(0, texture);
  node->getMaterial(0) = material;
}

NpcModel::~NpcModel(){
  if (node)
    node->remove();
  node = 0;

  if (mesh)
    mesh->drop();
	mesh = 0;

}