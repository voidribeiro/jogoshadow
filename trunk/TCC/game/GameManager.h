#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <iostream>
#include <map>

#include "../include/irrlicht.h"
#include "../core/Singleton.h"
#include "../core/EventListener.h"

//namescpaces
using namespace irr;
using namespace std;

class GameManager{
private:

  bool gameOver;
  
  IrrlichtDevice* device;
  irr::video::IVideoDriver* driver;
  irr::scene::ISceneManager* sceneManager;

  EventListener eventListener;
  
  irr::s32 lastFPS;
  //irr::s32 fps;
  //irr::u32 deltaTime;

  std::map <int, scene::IAnimatedMesh*> meshes;
  std::map <int, scene::ISceneNode*> nodes;

public:
  explicit GameManager();
  ~GameManager();

  bool init();

  void run();

  bool update();
  bool processLUAScripts();
  void draw();
  void displayWindowCaption();
  
  void pushMesh(const char* filename);
  void popMesh();

  //gets
  irr::video::IVideoDriver*  getVideoDriver() { return driver; }
  irr::scene::ISceneManager* getSceneManager(){ return sceneManager; }

  //irr::s32 getFPS();
  //irr::u32 getDeltaTime();

  friend class Singleton<GameManager>;

};

typedef Singleton<GameManager> gm;

#endif //_GAMEMANAGER_H_