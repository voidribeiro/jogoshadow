#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;
using namespace video;

class ObjectModel : public Model{
  private:
    IAnimatedMesh*  mesh;
    IMeshSceneNode* node;

  public:
    explicit ObjectModel();
    explicit ObjectModel(int id, int modelType, IAnimatedMesh* mesh, IMeshSceneNode* node);
    virtual ~ObjectModel();
    
    IAnimatedMesh*  getMesh() { return mesh; }
    ISceneNode*     getNode() { return node; }

};

#endif