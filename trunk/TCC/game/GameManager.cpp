#include "GameManager.h"

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

GameManager::GameManager(){}

GameManager::~GameManager(){

  nodes.clear();
  meshes.clear();

  device->drop();
}

bool GameManager::init(){

  bool succesful = false;
  
  lastFPS = -1;
  device = createDevice(video::EDT_DIRECT3D9, core::dimension2d<s32>(800, 600), 32, false, false, false, &eventListener);

  if (device != 0){
	  driver = device->getVideoDriver();
	  sceneManager = device->getSceneManager();
    succesful = true;
  }

  camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, 0, 0, true, 3.f);
  camera->setPosition(core::vector3df(-100,75,-150));

  /*
   * HARDCODE! remover depois
   */

	sceneManager->addLightSceneNode(0, core::vector3df(-60,300,100),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		600.0f);

  //create a skybox
  sceneManager->addSkyBoxSceneNode(
                driver->getTexture("resources/irrlicht2_up.jpg"),
                driver->getTexture("resources/irrlicht2_dn.jpg"),
                driver->getTexture("resources/irrlicht2_lf.jpg"),
                driver->getTexture("resources/irrlicht2_rt.jpg"),
                driver->getTexture("resources/irrlicht2_ft.jpg"),
                driver->getTexture("resources/irrlicht2_bk.jpg"));

  pushMesh("resources/plano.3DS");

  return succesful;
}

//adiciona uma Mesh e um Node aos respectivos maps
void GameManager::pushMesh(const char* filename){

  int meshIndex, nodeIndex;

  scene::IAnimatedMesh* tempMesh;
  scene::ISceneNode* tempNode;

  meshIt = meshes.begin();
  nodeIt = nodes.begin();

  meshIndex = (int) meshes.size();
  nodeIndex = (int) nodes.size();

  tempMesh = sceneManager->getMesh( filename );

  meshes.insert( meshIt, pair< int, scene::IAnimatedMesh* >( meshIndex, tempMesh ) );

  //sets the node
  if ( meshes.find(meshIndex)->second ){
    tempNode = sceneManager->addAnimatedMeshSceneNode( tempMesh );
    nodes.insert( nodeIt, pair< int,  scene::ISceneNode* >( nodeIndex, tempNode ) );
  }

}

void GameManager::popMesh(){
/*
  // isso remove o(s) node(s) também?
  irr::scene::IMeshCache* buf;

  buf = sceneManager->getMeshCache();
  buf->removeMesh( mesh );
*/
}

void GameManager::draw(){

  while(device->run()){

    if (device->isWindowActive()){
		  driver->beginScene(true, true, 0);

      sceneManager->drawAll();

      //draw everything
		  driver->endScene();
    }
    
    displayWindowCaption();

  }

}

void GameManager::displayWindowCaption(){
  irr::s32 fps = driver->getFPS();

  if (lastFPS != fps)
  {
	  core::stringw str = L"First time OOP enviorment walk - Irrlicht Engine [";
	  str += driver->getName();
	  str += "] FPS:";
	  str += fps;

	  device->setWindowCaption(str.c_str());
  }
}

bool GameManager::processLUAScripts(){
  luaScript.startScript("teste.lua");
  luaScript.endScript();
  return true;
}

bool GameManager::update(){
  //TODO
  return true;
}

void GameManager::run(){
  processLUAScripts();
  update();
  draw();
}