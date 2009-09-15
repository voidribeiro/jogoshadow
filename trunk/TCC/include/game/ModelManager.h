#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

/*

Name: ModelManager.h

Description:
  This class is responsible for hold all the references to the models in the game, Scenario, Hero, NPCs and Objects
  It has a map of pointers to Objects and NPCs models

*/


#include <map>

#include "ModelTypes.h"

//Boost includes
#include <noncopyable.hpp>

using namespace irr;
using namespace std;

class ModelManager: private boost::noncopyable{
private:

  /*
   * This class requires a pointer to the main SceneManager to create the Nodes and the Meshes
   */
  irr::scene::ISceneManager* sceneManager;
  
  /*
   * The Hero Model, assuming that there is only one hero, this instance is kept separatedly
   */
  HeroModel* hero; 

 /*
  * The Scenario Model, assuming that there is only one scenario, this instance is kept separatedly
  */
  ScenarioModel* scenario;

  /*
   * Map of all the Object Models in the scene
   * This map keeps the ID and the pointer to the ObjectModel instance
   */
  std::map <int, ObjectModel*> objects;

  /*
   * Map of all the NPC Models in the scene
   * This map keeps the ID and the pointer to the NpcModel instance
   */
  std::map <int, NpcModel*> npcs;


  SkeletalModel* skeleton;

  /*
   * This methods are used to make a cleaner code. They are used to get the SceneNode of the Object or the NPC map
   * based on the ID
   */
  scene::ISceneNode* getObjectNodeById(const int id);
  scene::IAnimatedMeshSceneNode* getNpcNodeById(const int id);

public:
  explicit ModelManager(irr::scene::ISceneManager* sm);
  virtual ~ModelManager();

  /*
   * create a Model based on Script
   */
  void pushModel(const char* filename, int modelType);

  void setHero      (const char* filename, ITexture* texture);
  void setScenario  (const char* filename);
  void setSkeleton  (const char* filename);

  void pushNpc      (const char* filename);
  void pushNpc      (const char* filename, ITexture* texture);
  void pushObject   (const char* filename, ITexture* texture);

  /* 
   * removes the ObjectModel from memory
   */
  void popObject(const int id);

  /* 
   * removes the NpcModel from memory
   */
  void popNpc(const int id);

  /*
   * Still Harcoded, but ModelManager has his own update function to change the SceneNodes.
   * This is useful because is possible to process Physics separetedly from the GameManager
   * changing the SceneNodes directly.
   * This function being here, allows it to run a different number of times from the main loop.
   */
  void update( position2di pos );

  ScenarioModel* getScenario() { return scenario; } 
  HeroModel*     getHero()     { return hero; } 
  SkeletalModel* getSkeleton() { return skeleton; } 

};

#endif