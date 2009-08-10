#include "ObjectModel.h"

ObjectModel::ObjectModel() : Model(){

}

ObjectModel::ObjectModel(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::IMeshSceneNode* node) 
: Model(id, modelType, mesh)
{
  this->node = node;
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