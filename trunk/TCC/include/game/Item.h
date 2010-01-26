#ifndef _ITEM_H_
#define _ITEM_H_

#include "string.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <list>

using namespace irr;
using namespace scene;
using namespace video;
using namespace std;

class Item{
private:
  string name;
  std::list <string> descriptionList;
  ITexture* image;
  GameObject* gameObject;
  bool isVisible;
  bool isInPlayerPosession;

public:
  explicit Item();
  explicit Item(const string name);
  virtual ~Item();

  void setGameObject(GameObject* obj){ gameObject = obj; }
  void addDescription(const string description);

  string getName(){ return name; }
  string getDescription(const int idx);
  ITexture* getImage(){ return image; }
  GameObject* getGameObject(){ return gameObject; }
  bool getVisible(){ return isVisible; }
  bool getInPlayerPosession(){ return isInPlayerPosession; }

};

#endif