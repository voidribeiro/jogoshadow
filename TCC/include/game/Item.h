#ifndef _ITEM_H_
#define _ITEM_H_

#include "string.h"
#include "TextureManager.h"

using namespace irr;
using namespace scene;
using namespace video;

class Item{
private:
  string name;
  string* description;

  ITexture* image;
  
  IAnimatedMesh* mesh;
  IAnimatedMeshSceneNode* node;

  bool isVisible;
  bool isInPlayerPosession;

public:
  explicit Item();
  explicit Item(const string name, const string description);
  virtual ~Item();

  string getName(){ return name; }
  string getDescription(){ return description[0]; }
  
  ITexture* getImage(){ return image; }

  IAnimatedMesh*          getMesh() { return mesh; }
  IAnimatedMeshSceneNode* getNode() { return node; }

};

#endif