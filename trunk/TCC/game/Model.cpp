#include "Model.h"

Model::Model(){

}

Model::Model(int id, int modelType, irr::scene::IAnimatedMesh* mesh){

  this->id = id;
  this->modelType = modelType;
  this->mesh = mesh;

}

Model::~Model(){
  if (mesh)
    mesh->drop();
	mesh = 0;
}