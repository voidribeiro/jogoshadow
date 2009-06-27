#include "GameManager.h"

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GameManager::GameManager(){}

/*
 * frees all IrrLicht allocated memory
 */
GameManager::~GameManager(){
  device->drop();
}

bool GameManager::init(){

  bool succesful = false;
  
  lastFPS = -1;
  
  /*
   * IrrLicht Main Device
   * instantiates all the engine
   * 
   *	IRRLICHT_API IrrlichtDevice* IRRCALLCONV createDevice(
	 *	  video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,
	 *	  const core::dimension2d<s32>& windowSize = (core::dimension2d<s32>(640,480)),
	 *	  u32 bits = 16,
	 *	  bool fullscreen = false,
	 *	  bool stencilbuffer = false,
	 *	  bool vsync = false,
	 *	  IEventReceiver* receiver = 0);
   */
  device = createDevice( video::EDT_DIRECT3D9, core::dimension2d<s32>(800, 600), 32, false, false, false, &eventListener );

  /*
   * retrives the pointers to video driver and sceneManager
   */
  if (device != 0){
	  driver = device->getVideoDriver();
	  sceneManager = device->getSceneManager();
    succesful = true;
  }

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
  camera = sceneManager->addCameraSceneNodeFPS( 0, 100.0f, .3f, -1, 0, 0, true, 3.f);
  camera->setPosition( core::vector3df( -100, 75, -150 ) );

  /*
   * instantiates the auxiliar managers
   */
  modelManager = new ModelManager( sceneManager );
  guiManager   = new GUIManager( device->getGUIEnvironment() ); 

  eventListener.setGUIManager( guiManager );

  /*
   * Plays a 2D backgound music using the SoundManager
   */

  if( !soundManager.init() )
    printf("Unable to initialize IrrKlang\n");
  else
    soundManager.playSound("resources/IrrlichtTheme.ogg",true);

  /*
   * HARDCODE!
   */

	sceneManager->addLightSceneNode(0, core::vector3df(-60,300,100),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		600.0f);

  /*
   * Creates a skybox
   */
  sceneManager->addSkyBoxSceneNode(
                driver->getTexture("resources/irrlicht2_up.jpg"),
                driver->getTexture("resources/irrlicht2_dn.jpg"),
                driver->getTexture("resources/irrlicht2_lf.jpg"),
                driver->getTexture("resources/irrlicht2_rt.jpg"),
                driver->getTexture("resources/irrlicht2_ft.jpg"),
                driver->getTexture("resources/irrlicht2_bk.jpg"));

  /* 
   * Creates a Scenario and a NPC
   */
  modelManager->pushModel("resources/plano.3DS", SCENARIO_MODEL);
  modelManager->pushModel("resources/faerie.md2", NPC_MODEL, driver->getTexture("resources/faerie2.bmp") );
  //modelManager->pushModel("resources/biped.X", NPC_MODEL);

  modelManager->pushModel("resources/skeleton/player.x", SKELETAL_MODEL);

  return succesful;
}

void GameManager::draw(){

  /*
   * while the device is running processes the main game loop
   */
  while(device->run()){

    if (device->isWindowActive()){
		  driver->beginScene(true, true, 0);

      /*
       * update all the elements positions, scales etc...
       */
      processLUAScripts();
      update();

      /*
       * Draws the scene and the GUI
       */
      sceneManager->drawAll();
      guiManager->drawAll();

		  driver->endScene();
    }
    
    displayWindowCaption();

  }

}

void GameManager::displayWindowCaption(){
  irr::s32 fps = driver->getFPS();

  if (lastFPS != fps)
  {
	  core::stringw str = L"Shadows of Time - Irrlicht Engine [";
	  str += driver->getName();
	  str += "] FPS:";
	  str += fps;

	  device->setWindowCaption(str.c_str());
  }
}

bool GameManager::processLUAScripts(){

  //The test folder could be some folder that specifies some stage

  //commented for performance issues

  //luaScript.startScript("LuaScripts/teste/teste.lua");
  //luaScript.endScript();
  return true;
}

bool GameManager::update(){
  modelManager->update();
  return true;
}

void GameManager::run(){
  draw();
}

irr::s32 GameManager::getFPS(){
  return driver->getFPS();
}

irr::u32 GameManager::getDeltaTime(){
  return device->getTimer()->getTime();
}