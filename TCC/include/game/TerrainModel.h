#ifndef _TERRAINMODEL_H_
#define _TERRAINMODEL_H_

#include "Model.h"

using namespace irr;
using namespace scene;

class TerrainModel{
  private:
    int id;
    ITerrainSceneNode* terrain;
    ITriangleSelector* selector;

  public:
    explicit TerrainModel();
    explicit TerrainModel(const int id, ITerrainSceneNode* node, ITriangleSelector* selector);
    virtual ~TerrainModel();
    
    ITerrainSceneNode* getNode() { return terrain; }
    ITriangleSelector* getSelector() { return selector; }

};


#endif