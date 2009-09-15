#include "ModelManager.h"

ModelManager::ModelManager(irr::scene::ISceneManager* sm)
: hero(), skeleton(),scenario(){
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

void ModelManager::setHero(const char *filename, ITexture* texture){
  scene::IAnimatedMesh* mesh;
  scene::IAnimatedMeshSceneNode* animatedNode;

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

  animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

  if(hero){
    hero->~HeroModel();
    hero = 0;
  }

  /*
   * Create a HeroModel
   *
   *  HeroModel(
   *   int id, 
   *   int modelType, 
   *   IAnimatedMesh* mesh, 
   *   IAnimatedMeshSceneNode* node) 
   */
  hero = new HeroModel(1, HERO_MODEL, mesh, animatedNode, texture);
}

void ModelManager::setScenario(const char *filename){
  scene::IAnimatedMesh* mesh;
  scene::ISceneNode* scenarioNode;
  scene::ITriangleSelector* selector;

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

  scenarioNode = sceneManager->addOctTreeSceneNode( mesh );
  selector = sceneManager->createOctTreeTriangleSelector( mesh, scenarioNode, 256 );

  if(scenario){
    scenario->~ScenarioModel();
    scenario = 0;
  }

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
}

void ModelManager::setSkeleton(const char *filename){
  scene::IAnimatedMesh* mesh;
  scene::IAnimatedMeshSceneNode* animatedNode;

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

  animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

  if(skeleton){
    skeleton->~SkeletalModel();
    skeleton = 0;
  }

  /*
   *  SkeletalModel( 
   *    int id, 
   *    int modelType, 
   *    IAnimatedMesh* mesh, 
   *    IAnimatedMeshSceneNode* node, 
   *    u32 animationSpeed )
   */

  skeleton = new SkeletalModel(5, SKELETAL_MODEL, mesh, animatedNode, 8);
  skeleton->setAnimType(CSK_ANIM_WALK);
  skeleton->getSkeletonSceneNode()->setPosition( core::vector3df(80,30,-50) );
}

void ModelManager::pushNpc(const char *filename, ITexture* texture){
  NpcModel* npc;
  scene::IAnimatedMesh* mesh;
  scene::IAnimatedMeshSceneNode* animatedNode;
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

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

  animatedNode->setMD2Animation(scene::EMAT_STAND);
  animatedNode->setAnimationSpeed(60);
}

void ModelManager::pushNpc(const char *filename){
  NpcModel* npc;
  scene::IAnimatedMesh* mesh;
  scene::IAnimatedMeshSceneNode* animatedNode;
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

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
  npc = new NpcModel( (int)npcs.size(), NPC_MODEL, mesh, animatedNode);
  npcs.insert(npcIt, pair<int, NpcModel*>( (int)npcs.size(), npc) );

  animatedNode->setMD2Animation(scene::EMAT_STAND);
  animatedNode->setAnimationSpeed(60);
}



void ModelManager::pushObject(const char *filename, ITexture* texture){
  ObjectModel* obj;
  scene::IAnimatedMesh* mesh;
  scene::IMeshSceneNode* staticNode;
  std::map <int, ObjectModel*>::iterator objIt = objects.end();

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

  staticNode = sceneManager->addMeshSceneNode( mesh );

  /*
   * Create a ObjectModel and push it to the Object map
   *
   * ObjectModel(
   *   int id, 
   *   int modelType, 
   *   IAnimatedMesh* mesh, 
   *   IMeshSceneNode* node) 
   */
  obj = new ObjectModel( (int)objects.size(), OBJECT_MODEL, mesh, staticNode);
  objects.insert(objIt, pair<int, ObjectModel*>( (int)objects.size(), obj) );

}

void ModelManager::pushModel(const char *filename, int modelType){
  switch(modelType){
    case HERO_MODEL:
      //setHero(filename, texture);
      break;

    case SCENARIO_MODEL:
      setScenario(filename);
      break;

    case NPC_MODEL:
      pushNpc(filename);
      break;

    case OBJECT_MODEL:
      //pushObject(filename, texture);
      break;

    case SKELETAL_MODEL:
      setSkeleton(filename);
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
  /*
  escala no cenário afeta o triangleSelector!
  scenario->getNode()->setScale( irr::core::vector3df(1,1,1) );
  */
  

  /*
   * changes the NPC position
   */
  /*
  getNpcNodeById(0)->setPosition(irr::core::vector3df(0,30,0));
  */

  IAnimatedMeshSceneNode* node;
  node = skeleton->getSkeletonSceneNode();

  node->setScale( core::vector3df(8,8,8) );

  /* ponto onde o modelo olha */
  skeleton->animSkeleton( pos );
}

scene::ISceneNode* ModelManager::getObjectNodeById(const int id){
  return objects.find(id)->second->getNode();
}

scene::IAnimatedMeshSceneNode* ModelManager::getNpcNodeById(const int id){
  return npcs.find(id)->second->getNode();
}