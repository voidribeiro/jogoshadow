#ifndef _ITEM_H_
#define _ITEM_H_

#include "string.h"
#include "TextureManager.h"

class Item{
private:
  string name;
  string[] description;

  ITexture* image;
  
  IAnimatedMesh* mesh;
  IAnimatedMeshSceneNode* node;

  bool isVisible;
  bool isInPlayerPosession;

public:
  explicit Item();
  explicit Item(string name, string description);
  virtual ~Item();

  static void view();

};

#endif