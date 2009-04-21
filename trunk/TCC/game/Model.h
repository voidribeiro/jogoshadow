#ifndef _MODEL_H_
#define _MODEL_H_

#include "../include/irrlicht.h"

class Model{
  private:
    int id;
    int modelType;

    irr::scene::IAnimatedMesh* mesh;

  public:

    Model();
    Model(int id, int modelType, irr::scene::IAnimatedMesh* mesh);
    ~Model();

    irr::scene::IAnimatedMesh* getMesh() { return mesh; }

};

#endif