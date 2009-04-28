#ifndef _MODEL_H_
#define _MODEL_H_

/*

Name: Model.h

Description:

  This is the base class used to hold a Model. 

  A model is composed by a mesh, an unique ID, and a modelType, according to the enum in ModelTypes.h.

  Since a mesh needs a respective node, specializations of each modelType were created to support this
  (HeroModel, ScenarioModel, NpcModel and ObjectModel), each one with specific characteristics of node.

*/

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