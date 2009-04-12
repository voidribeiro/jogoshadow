#ifndef _MODEL_H_
#define _MODEL_H_

#include "../include/irrlicht.h"

class Model{
  private:
    int id;
    int modelType;

    irr::scene::IAnimatedMesh* mesh;
    irr::scene::ISceneNode* node;

  public:

    Model();
    Model(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* node);
    ~Model();

    irr::scene::IAnimatedMesh* getMesh() { return mesh; }
    irr::scene::ISceneNode* getNode() { return node; }

};

#endif