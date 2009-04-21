#ifndef _MODELHMANAGER_H_
#define _MODELMANAGER_H_

#include <map>

//#include "../include/irrlicht.h"

#include "ModelTypes.h"

using namespace irr;
using namespace std;

class ModelManager{
private:

  irr::scene::ISceneManager* sceneManager;
  
  //a princípio vou estipular que o modelo do Hero tem id = 1 SEMPRE (por ser o mesmo valor do ENUM no ModelTypes.h inclusive)
  HeroModel* hero; 
  //a princípio vou estipular que o modelo do Scenario tem id = 2 SEMPRE (por ser o mesmo valor do ENUM no ModelTypes.h inclusive)
  ScenarioModel* scenario;

  //map de todos os objetos na cena
  std::map <int, ObjectModel*> objects;

  //map com todos os NPCs da cena
  std::map <int, NpcModel*> npcs;

  //estes métodos estão privados por ser responsabilidade da Clase ModelManager tratar os maps de Model
  scene::ISceneNode* getObjectNodeById(int id);
  scene::IAnimatedMeshSceneNode* getNpcNodeById(int id);

public:
  ModelManager(irr::scene::ISceneManager* sm);
  ~ModelManager();

  //adiciona um modelo sem textura
  void pushModel(const char* filename, int modelType);

  //adiciona um modelo com textura
  void pushModel(const char* filename, int modelType, ITexture* texture);

  void popModel();

  void update();

};

#endif