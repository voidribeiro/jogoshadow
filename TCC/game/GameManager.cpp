#include "GameManager.h"

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GameManager::GameManager(std::string path){
  //TODO - Remove this hack
  int pos = path.find("TCC.exe");
  this->path = path.substr(0,pos);
  GameBinder::game = new Game(this->path);   
} 

/*
 * frees all IrrLicht allocated memory
 */
GameManager::~GameManager(){
  delete(GameBinder::game);
  IrrlichtDevice* device = DeviceManager::GetDevice();
  device->drop();
}

bool GameManager::init(){

  bool succesful = true;
  
  lastFPS = -1;
  
  DeviceManager::initialize();
  IrrlichtDevice* device = DeviceManager::GetDevice();

  sceneManager = device->getSceneManager();

  GameBinder::game->LoadLevel("Start");

  /*
   * Sets the main camera
   *
   *		virtual ICameraSceneNode* addCameraSceneNodeFPS(
   *     ISceneNode* parent = 0,
	 *		 f32 rotateSpeed = 100.0f, 
   *     f32 moveSpeed = .5f, 
   *     s32 id=-1,
	 *		 SKeyMap* keyMapArray=0, 
   *     s32 keyMapSize=0, 
   *     bool noVerticalMovement=false,
	 *	   f32 jumpSpeed = 0.f) = 0;
   */
  //camera = sceneManager->addCameraSceneNodeFPS( 0, 100.0f, .3f, -1, 0, 0, false, 3.f);
  camera = sceneManager->addCameraSceneNode();
  camera->setPosition( core::vector3df( 100, 150, 150 ) );

  /*
   * HARDCODE!
   */

  sceneManager->addLightSceneNode(0, core::vector3df(-60,200,-100),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		600.0f);

  return succesful;
}

void GameManager::draw(){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  sceneManager->drawAll();
  env->drawAll();

}

bool GameManager::displayWindowCaption(){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();

  irr::s32 fps = driver->getFPS();

  if (lastFPS != fps){
	  core::stringw str = L"Shadows of Time - Irrlicht Engine [";
	  str += driver->getName();
	  str += "] FPS:";
	  str += fps;

	  device->setWindowCaption(str.c_str());
  }
  return true;
}

bool GameManager::update(){
  return true;
}

void GameManager::run(){
  /*
   * while the device is running, processes the main game loop
   */
  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();

  while(device->run() && !GameBinder::game->IsGameOver() ){

    if (device->isWindowActive()){
		  driver->beginScene(true, true, 0);

      update();
      draw();

      GameObjectMap::Update();
      GameObjectMap::Draw();

      if (!GameObjectMap::levelToLoad.empty()){
        GameBinder::game->LoadLevel(GameObjectMap::levelToLoad);
        GameObjectMap::levelToLoad.clear();
      }

		  driver->endScene();
    }

    displayWindowCaption();

  }
  
}

irr::s32 GameManager::getFPS(){
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  return driver->getFPS();
}

irr::u32 GameManager::getDeltaTime(){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  return device->getTimer()->getTime();
}
