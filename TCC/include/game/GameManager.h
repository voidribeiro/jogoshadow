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
#include <string>

#include "noncopyable.hpp"

#include "game.h"

#include "DeviceManager.h"
#include "Singleton.h"
#include "Script.h"
#include "TextureManager.h"

using namespace irr;
using namespace std;

class GameManager : private boost::noncopyable
{
private:

 std::string path;

  irr::scene::ISceneManager* sceneManager;
  irr::scene::ICameraSceneNode* camera;

  irr::s32 lastFPS;

public:
  explicit GameManager(std::string path);
  virtual ~GameManager();

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
   * Draw all elements, models, scene, GUI etc...
   */
  void draw();

  /*
   * Updates the window caption with FPS
   */
  bool displayWindowCaption();
  

  //gets
  irr::scene::ISceneManager* getSceneManager(){ return sceneManager; }

  irr::s32 getFPS();
  irr::u32 getDeltaTime();

  friend class Singleton<GameManager>;
};

typedef Singleton<GameManager> gm;

#endif //_GAMEMANAGER_H_