#include "Model.h"

Model::Model(){

}

Model::Model(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* node){

  this->id = id;
  this->modelType = modelType;
  this->mesh = mesh;
  this->node = node;
}

Model::~Model(){

}