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
}

/*
 * frees all IrrLicht allocated memory
 */
GameManager::~GameManager(){
  IrrlichtDevice* device = DeviceManager::getInstance()->getDevice();
  device->drop();
}

bool GameManager::init(){

  bool succesful = true;
  
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
  DeviceManager::getInstance()->initialize(&eventListener);
  IrrlichtDevice* device = DeviceManager::getInstance()->getDevice();

  sceneManager = device->getSceneManager();

  /*
   * instantiates the auxiliar managers
   */
  modelManager = new ModelManager( sceneManager );
  guiManager   = new GUIManager( device->getGUIEnvironment(), device->getVideoDriver() );
  textureManager = new TextureManager();

  eventListener.setGUIManager( guiManager );

  /*
	Using the loader
  */
  Factory factory;
  factory.setModelFactory(modelManager);

  FactoryBinder binder;
  binder.factory = &factory;

  Loader loader(path);
  loader.RegisterFunction(binder.registerFunctions);
  loader.LoadLevel("Level1");

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
  camera = sceneManager->addCameraSceneNodeFPS( 0, 100.0f, .3f, -1, 0, 0, false, 3.f);
  camera->setPosition( core::vector3df( -100, 75, -150 ) );

  /*
   * Plays a 2D backgound music using the SoundManager
  
  */

  if( !soundManager.init() )
    printf("Unable to initialize IrrKlang\n");
  else;
    //soundManager.playSound("resources/IrrlichtTheme.ogg",true);

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
				textureManager->GetTexture("resources/irrlicht2_up.jpg"),
				textureManager->GetTexture("resources/irrlicht2_dn.jpg"),
				textureManager->GetTexture("resources/irrlicht2_lf.jpg"),
				textureManager->GetTexture("resources/irrlicht2_rt.jpg"),
				textureManager->GetTexture("resources/irrlicht2_ft.jpg"),
				textureManager->GetTexture("resources/irrlicht2_bk.jpg"));

  /* 
   * Creates a Scenario and a NPC
   */
  modelManager->setScenario("resources/plano.3DS");
  modelManager->setTerrain( "resources/terrain-heightmap.bmp", 
                            textureManager->GetTexture("resources/terrain-texture.jpg"),
                            textureManager->GetTexture("resources/detailmap3.jpg"));

  //modelManager->pushModel("resources/plano.3DS", SCENARIO_MODEL);
  //modelManager->pushModel("resources/faerie.md2", NPC_MODEL, driver->getTexture("resources/faerie2.bmp") );

  modelManager->setSkeleton("resources/skeleton/player.x");
  //modelManager->pushNpc("resources/faerie.md2");
  //modelManager->pushModel("resources/skeleton/player.x", SKELETAL_MODEL);

  pm.push(process1, this);
  pm.push(process2, this);

  //modelManager->popNpc(0);

  return succesful;
}

void GameManager::draw(){
      
  sceneManager->drawAll();
  guiManager->drawAll();
  
  Image2D image("resources/001shot.jpg",textureManager);
  image.draw();

  drawTriangleSelection();

  //return true;

}

void GameManager::drawTriangleSelection(){

  IrrlichtDevice* device = DeviceManager::getInstance()->getDevice();
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();

	core::line3d<f32> line;
	line.start = camera->getPosition();
	line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;

	core::vector3df intersection;
  core::triangle3df tri;

  ITriangleSelector* selector;

  for(int i = 0; i < modelManager->getNpcCount(); i++ ){
    selector = modelManager->getNpcById(i)->getSelector();
    if (sceneManager->getSceneCollisionManager()->getCollisionPoint(
	    line, selector, intersection, tri)){

      driver->draw3DTriangle(tri, video::SColor(255,0,255,0));
      return;
    }
  }

  selector = modelManager->getTerrain()->getSelector();
  if (sceneManager->getSceneCollisionManager()->getCollisionPoint(
		line, selector, intersection, tri)){

    driver->draw3DTriangle(tri, video::SColor(255,255,0,0));

    //mudar isso de lugar depois
    modelManager->animateSkeleton(intersection, eventListener.GetMouseState().LeftButtonDown );
  }

}

bool GameManager::displayWindowCaption(){
  IrrlichtDevice* device = DeviceManager::getInstance()->getDevice();
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();

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

bool GameManager::processLUAScripts(){

  //The test folder could be some folder that specifies some stage

  //commented for performance issues

  //luaScript.startScript("LuaScripts/teste/teste.lua");
  //luaScript.endScript();
  return true;
}

bool GameManager::update(){

  //pm.process();
  position2di pos = eventListener.GetMouseState().pos;
  modelManager->update( pos );

  return true;
}

void GameManager::run(){
  /*
   * while the device is running, processes the main game loop
   */
  IrrlichtDevice* device = DeviceManager::getInstance()->getDevice();
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();

  while(device->run()){

    if (device->isWindowActive()){
		  driver->beginScene(true, true, 0);

      update();
      draw();

		  driver->endScene();
    }

    displayWindowCaption();

  }
  
}

irr::s32 GameManager::getFPS(){
  irr::video::IVideoDriver* driver = DeviceManager::getInstance()->getDriver();
  return driver->getFPS();
}

irr::u32 GameManager::getDeltaTime(){
  IrrlichtDevice* device = DeviceManager::getInstance()->getDevice();
  return device->getTimer()->getTime();
}

void GameManager::process1(void *ptr, long purpose){
  GameManager* gm = (GameManager*) ptr;
  printf("p1!\n");
}

void GameManager::process2(void *ptr, long purpose){
  printf("p2!\n");
}