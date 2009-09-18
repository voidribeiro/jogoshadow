#include "ObjectModel.h"

ObjectModel::ObjectModel() : Model(){

}

ObjectModel::ObjectModel(int id, int modelType, IAnimatedMesh* _mesh, IMeshSceneNode* _node) 
: Model(id, modelType), mesh(_mesh), node(_node){

}

ObjectModel::~ObjectModel(){
  if (node)
    node->remove();
  node = 0;
  //delete node;

  if (mesh)
    mesh->drop();
  mesh = 0;
  //delete mesh;

}