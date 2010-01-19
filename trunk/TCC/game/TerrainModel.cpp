#include "TerrainModel.h"

TerrainModel::TerrainModel(){

}

TerrainModel::TerrainModel(const int id, ITerrainSceneNode* node, ITriangleSelector* _selector) 
: id(id), terrain(node), selector(_selector)
{
  terrain->setTriangleSelector(selector);
  //terrain->setVisible(false);
}

TerrainModel::~TerrainModel(){
  if(selector)
    selector->drop();
  
  if(terrain)
    terrain->drop();
}