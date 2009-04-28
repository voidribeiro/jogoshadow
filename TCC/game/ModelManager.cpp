#include "ModelManager.h"

ModelManager::ModelManager(irr::scene::ISceneManager* sm){
  sceneManager = sm;
}

/*
 * Clear both Model maps
 */
ModelManager::~ModelManager(){
 objects.clear();
 npcs.clear();
}

void ModelManager::pushModel(const char *filename, int modelType){
  /*
   * Mesh used by all models
   */
  scene::IAnimatedMesh* mesh;

  /*
   * Specific nodes based on each type of Model
   */
  scene::ISceneNode* scenarioNode;
  scene::IAnimatedMeshSceneNode* animatedNode;
  scene::IMeshSceneNode* staticNode;

  /*
   * Triangle selector used by ScenarioModel
   */
  scene::ITriangleSelector* selector;

  /*
   * Iterators to the maps
   */
  std::map <int, ObjectModel*>::iterator objIt = objects.end();
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();

  /*
   * Bufers for NPC and Object Models
   */
  NpcModel* npc;
  ObjectModel* obj;

  mesh = sceneManager->getMesh( filename );

  /*
   * Returns if the mesh can't be created
   */
  if(!mesh)
    return;

  /*
   * Creates the model based on parameter modelType
   */
  switch(modelType){
    case HERO_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );
      /*
       * Create a HeroModel
       *
       *  HeroModel(
       *   int id, 
       *   int modelType, 
       *   IAnimatedMesh* mesh, 
       *   IAnimatedMeshSceneNode* node) 
       */
      hero = new HeroModel(1, HERO_MODEL, mesh, animatedNode);
      break;

    case SCENARIO_MODEL:
      scenarioNode = sceneManager->addOctTreeSceneNode( mesh );
      selector = sceneManager->createOctTreeTriangleSelector( mesh, scenarioNode, 128 );

      /*
       * Create a ScenarioModel
       *
       *  ScenarioModel(
       *   int id, 
       *   int modelType, 
       *   IAnimatedMesh* mesh, 
       *   ISceneNode* node, 
       *   ITriangleSelector* selector) 
       */
      scenario = new ScenarioModel(2, SCENARIO_MODEL, mesh, scenarioNode, selector);
      break;

    case NPC_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

      /*
       * Create a NpcModel and push it to the NPC map
       *
       *  NpcModel(
       *   int id, 
       *   int modelType, 
       *   IAnimatedMesh* mesh, 
       *   IAnimatedMeshSceneNode* node)
       */
      npc = new NpcModel( (int)npcs.size(), NPC_MODEL, mesh, animatedNode);
      npcs.insert(npcIt, pair<int, NpcModel*>( (int)npcs.size(), npc) );

      break;

    case OBJECT_MODEL:
      staticNode = sceneManager->addMeshSceneNode( mesh );

      /*
       * Create a NpcModel and push it to the NPC map
       *
       * ObjectModel(
       *   int id, 
       *   int modelType, 
       *   IAnimatedMesh* mesh, 
       *   IMeshSceneNode* node) 
       */
      obj = new ObjectModel( (int)objects.size(), OBJECT_MODEL, mesh, staticNode);
      objects.insert(objIt, pair<int, ObjectModel*>( (int)objects.size(), obj) );
      break;

    case SKELETAL_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );
      skeleton = new SkeletalModel(5,SKELETAL_MODEL, mesh, animatedNode, 2);
      skeleton->setAnimType(CSK_ANIM_WALK);

      break;
  }

}

void ModelManager::pushModel(const char *filename, int modelType, ITexture* texture){
  /*
   * Mesh used by all models
   */
  scene::IAnimatedMesh* mesh;

  /*
   * Specific nodes based on each type of Model
   */
  scene::IAnimatedMeshSceneNode* animatedNode;

  /*
   * Iterator to the maps
   */
  std::map <int, ObjectModel*>::iterator objIt = objects.end();
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();

  /*
   * Buffer Objects
   */
  NpcModel* npc;

  mesh = sceneManager->getMesh( filename );
  
  /*
   * Returns if the mesh can't be created
   */
  if(!mesh)
    return;

  /*
   * Creates the model based on parameter modelType
   */
  switch(modelType){
    case NPC_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

      /*
       * Create a NpcModel with texture and push it to the NPC map
       *
       *  NpcModel(
       *   int id, 
       *   int modelType, 
       *   IAnimatedMesh* mesh, 
       *   IAnimatedMeshSceneNode* node,
       *   ITexture* texture)
       */
      npc = new NpcModel( (int)npcs.size(), NPC_MODEL, mesh, animatedNode, texture);
      npcs.insert(npcIt, pair<int, NpcModel*>( (int)npcs.size(), npc) );

      /*
       * HARDCODE! changing animation and animationSpeed to a MD2 file
       */
      getNpcNodeById( 0 )->setMD2Animation(scene::EMAT_STAND);
      getNpcNodeById( 0 )->setAnimationSpeed(60);
      break;

  }

}


void ModelManager::popModel(){
	/*
  if (mesh)
		mesh->remove();
	mesh = 0;
  */
}

void ModelManager::update(){

  /*
   * changes the scenario scale
   */
  scenario->getNode()->setScale( irr::core::vector3df(1,1,2) );

  /*
   * changes the NPC position
   */
  getNpcNodeById(0)->setPosition(irr::core::vector3df(0,30,0));

  skeleton->getSkeletonSceneNode()->setScale( core::vector3df(8,8,8) );
  skeleton->getSkeletonSceneNode()->setPosition( core::vector3df(50,30,-50) );

  skeleton->animSkeleton( core::position2di(200,10) );
}

scene::ISceneNode* ModelManager::getObjectNodeById(int id){
  return objects.find(id)->second->getNode();
}

scene::IAnimatedMeshSceneNode* ModelManager::getNpcNodeById(int id){
  return npcs.find(id)->second->getNode();
}