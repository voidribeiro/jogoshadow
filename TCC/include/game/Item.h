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
  string imageName;

  bool modelIsVisible;      //se o modelo está visível
  bool imageIsVisible;      //se a imagem 2D está visível
  bool isInPlayerPosession; //se o jogador possui o ítem

public:
  explicit Item();
  explicit Item(const string name, const bool _modelIsVisible, const bool _isInPlayerPosession);
  virtual ~Item();

  void addDescription(const string description);
  void drawImage(int posX, int posY);

  void setModelVisible(bool b){ modelIsVisible = b; }
  void setImageVisible(bool b){ imageIsVisible = b; }
  void setPlayerPosession(bool b){ isInPlayerPosession = b; }

  string getName(){ return name; }
  string getDescription(const int idx);
  string getImage(){ return imageName; }

  bool getModelVisible(){ return modelIsVisible; }
  bool getImageVisible(){ return imageIsVisible; }
  bool getInPlayerPosession(){ return isInPlayerPosession; }

};

#endif