#include "ModelManager.h"

ModelManager::ModelManager(irr::scene::ISceneManager* sm){
  sceneManager = sm;
}

/*
 * Clear both Model maps
 */
ModelManager::~ModelManager(){
  std::map <int, ObjectModel*>::iterator objIt;
  std::map <int, NpcModel*>::iterator npcIt;

  for ( objIt = objects.begin(); objIt != objects.end(); objIt++ ){
    //objects.find(objIt)->second->~ObjectModel();
    objects.erase(objIt);
  }

  for ( npcIt = npcs.begin(); npcIt != npcs.end(); npcIt++ ){
    //npcs.find(npcIt)->second->~NpcModel();
    npcs.erase(npcIt);
  }

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
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();
  std::map <int, ObjectModel*>::iterator objIt = objects.end();

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
      selector = sceneManager->createOctTreeTriangleSelector( mesh, scenarioNode, 256 );

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

      /*
       *  SkeletalModel( 
       *    int id, 
       *    int modelType, 
       *    IAnimatedMesh* mesh, 
       *    IAnimatedMeshSceneNode* node, 
       *    u32 animationSpeed )
       *
       */
      skeleton = new SkeletalModel(5,SKELETAL_MODEL, mesh, animatedNode, 8);
      
      skeleton->setAnimType(CSK_ANIM_WALK);

      skeleton->getSkeletonSceneNode()->setPosition( core::vector3df(80,30,-50) );

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
    case HERO_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );
      /*
       * Create a HeroModel
       *
       *  HeroModel(
       *   int id, 
       *   int modelType, 
       *   IAnimatedMesh* mesh, 
       *   IAnimatedMeshSceneNode* node,
       *   ITexture* texture) 
       */
      hero = new HeroModel(1, HERO_MODEL, mesh, animatedNode, texture);
      break;

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
      animatedNode->setMD2Animation(scene::EMAT_STAND);
      animatedNode->setAnimationSpeed(60);
      break;

  }

}

void ModelManager::popObject(const int id){

  std::map <int, ObjectModel*>::iterator objIt;
  objIt = objects.find(id);

  //se não encontrar um objeto no map
  if(objIt == objects.end())
    return;

  objIt->second->~ObjectModel();

}

void ModelManager::popNpc(const int id){
  std::map <int, NpcModel*>::iterator npcIt;
  npcIt = npcs.find(id);

  //se não encontrar um objeto no map
  if(npcIt == npcs.end())
    return;

  npcIt->second->~NpcModel();
}


void ModelManager::update(position2di pos){

  /*
   * changes the scenario scale
   */
  //escala no cenário afeta o triangleSelector!
  //scenario->getNode()->setScale( irr::core::vector3df(1,1,1) );
  

  /*
   * changes the NPC position
   */
  //getNpcNodeById(0)->setPosition(irr::core::vector3df(0,30,0));

  IAnimatedMeshSceneNode* node;
  node = skeleton->getSkeletonSceneNode();

  node->setScale( core::vector3df(8,8,8) );

  //ponto onde o modelo olha
  skeleton->animSkeleton( pos );
}

scene::ISceneNode* ModelManager::getObjectNodeById(int id){
  return objects.find(id)->second->getNode();
}

scene::IAnimatedMeshSceneNode* ModelManager::getNpcNodeById(int id){
  return npcs.find(id)->second->getNode();
}