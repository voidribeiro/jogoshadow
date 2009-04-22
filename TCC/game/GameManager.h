#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

/*

Name: GameManager.h

Description:
This is the core class of the game, it is responsible for the main game loop and to agregate all 
the game features making them interact correctly.

*/


#include <iostream>
#include <map>

#include "../core/Singleton.h"
#include "../core/EventListener.h"
#include "../core/Script.h"
#include "../core/GUIManager.h"

#include "ModelManager.h"
#include "SoundManager.h"

using namespace irr;
using namespace std;

class GameManager{
private:

  bool gameOver;

  /*
   *main IrrLicht device, needed to run everything in the engine
   */
  IrrlichtDevice* device;

  irr::video::IVideoDriver* driver;
  irr::scene::ISceneManager* sceneManager;
  irr::scene::ICameraSceneNode* camera;

  Script luaScript;
  
  EventListener eventListener;

  ModelManager* modelManager;
  GUIManager*   guiManager;
  SoundManager  soundManager;

  irr::s32 lastFPS;
  //irr::s32 fps;
  //irr::u32 deltaTime;


public:
  explicit GameManager();
  ~GameManager();

  /* 
   * initialization function, makes startup tests and instantiate the base classes
   */
  bool init();

  /*
   * game loop
   */
  void run();

  /*
   * Updates all game elements and processes all game logics
   */
  bool update();

  /*
   * Processes all lua script calls
   */
  bool processLUAScripts();

  /*
   * Draw all elements, models, scene, GUI etc...
   */
  void draw();

  /*
   * Updates the window caption with FPS
   */
  void displayWindowCaption();
  
  //gets
  irr::video::IVideoDriver*  getVideoDriver() { return driver; }
  irr::scene::ISceneManager* getSceneManager(){ return sceneManager; }

  irr::s32 getFPS();
  irr::u32 getDeltaTime();

  friend class Singleton<GameManager>;

};

typedef Singleton<GameManager> gm;

#endif //_GAMEMANAGER_H_