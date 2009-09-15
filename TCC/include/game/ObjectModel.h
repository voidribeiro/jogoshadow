#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

#include "Model.h"

class ObjectModel : public Model{
  private:
    irr::scene::IMeshSceneNode* node;

  public:
    explicit ObjectModel();
    explicit ObjectModel(int id, int modelType, irr::scene::IAnimatedMesh* mesh, irr::scene::IMeshSceneNode* node);
    virtual ~ObjectModel();
    
    irr::scene::ISceneNode* getNode() { return node; }

};

#endif