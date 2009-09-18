#ifndef _MODEL_H_
#define _MODEL_H_

/*

Name: Model.h

Description:

  This is the base class used to hold a Model. 

  A model is composed by a unique ID, and a modelType, according to the enum in ModelTypes.h.

  Since a mesh needs a respective node, specializations of each modelType were created to support this,
  each one with specific characteristics of mesh and node.

*/

#include "irrlicht.h"

class Model{
  protected:
    int id;
    int modelType;

  public:

    explicit Model(){}
    explicit Model(const int id, int modelType):id(id), modelType(modelType){}
    virtual ~Model(){}

};

#endif