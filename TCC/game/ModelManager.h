#ifndef _MODELHMANAGER_H_
#define _MODELMANAGER_H_

#include <map>

//#include "../include/irrlicht.h"

#include "ModelTypes.h"
#include "Model.h"

using namespace irr;
using namespace std;

class ModelManager{
private:

  irr::scene::ISceneManager* sceneManager;
  
  std::map <int, Model*> models;

public:
  ModelManager(irr::scene::ISceneManager* sm);
  ~ModelManager();

  void pushModel(const char* filename, int modelType);
  void popModel();

  void update();

};

#endif