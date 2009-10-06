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

  delete scenario;
  delete terrain;
}

void ModelManager::setHero(const char *filename, ITexture* texture){
  scene::IAnimatedMesh* mesh;
  scene::IAnimatedMeshSceneNode* animatedNode;

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

  animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

  if(hero)
    hero->~HeroModel();

  /*
   * Create a HeroModel
   *
   *  HeroModel(
   *   int id, 
   *   int modelType, 
   *   IAnimatedMesh* mesh, 
   *   IAnimatedMeshSceneNode* node) 
   */
  boost::shared_ptr<HeroModel> hero (new HeroModel(1, mesh, animatedNode, texture));
}

void ModelManager::setScenario(const char *filename){
  scene::IAnimatedMesh* mesh;
  scene::ISceneNode* scenarioNode;
  scene::ITriangleSelector* selector;

  mesh = sceneManager->getMesh( filename );

  if(!mesh)
    return;

  scenarioNode = sceneManager->addOctTreeSceneNode( mesh );
  //scenarioNode = sceneManager->addTerrainSceneNode( mesh );
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
  scenario = new ScenarioModel(2, mesh, scenarioNode, selector);
}

void ModelManager::setTerrain(const char *filename, ITexture* texture0, ITexture* texture1){
  //scene::IAnimatedMesh* mesh;
  scene::ITerrainSceneNode* terrainNode;
  scene::ITriangleSelector* selector;

  //mesh = sceneManager->getMesh( filename );

  //if(!mesh)
  //  return;

  terrainNode = sceneManager->addTerrainSceneNode(
                filename,
                0,                                      // parent node
                -1,                                     // node id
                core::vector3df(-50.0f, -350.0f, 0.f),      // position
                core::vector3df(0.f, 0.f, 0.f),         // rotation
                core::vector3df(40.f, 4.4f, 40.f),      // scale
                video::SColor ( 255, 255, 255, 255 ),   // vertexColor
                5,                                      // maxLOD
                scene::ETPS_17,                         // patchSize
                4                                       // smoothFactor
                );

  //scenarioNode = sceneManager->addTerrainSceneNode( mesh );
  selector = sceneManager->createTerrainTriangleSelector( terrainNode, 0 );

	terrainNode->setMaterialFlag(video::EMF_LIGHTING, false);

	terrainNode->setMaterialTexture(0,texture0);
	terrainNode->setMaterialTexture(1,texture1);
	
	terrainNode->setMaterialType(video::EMT_DETAIL_MAP);

	terrainNode->scaleTexture(1.0f, 20.0f);

//  if(terrain)
//    terrain->~TerrainModel();

  terrain = new TerrainModel(6, terrainNode, selector);

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

  skeleton = new SkeletalModel(5, mesh, animatedNode, 8);
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
  npc = new NpcModel( (int)npcs.size(), mesh, animatedNode, texture);
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
  npc = new NpcModel( (int)npcs.size(), mesh, animatedNode);
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

void ModelManager::animateSkeleton(vector3df pos, bool mousePresed){

  IAnimatedMeshSceneNode* node = getSkeleton()->getSkeletonSceneNode();
  scene::ISceneNodeAnimator* anim;

  pos.Y += 30;

  anim =	sceneManager->createFlyStraightAnimator(node->getPosition(), pos, 10 * pos.getDistanceFrom(node->getPosition()), false);

  if(pos.getDistanceFrom(node->getPosition()) < 1.0f)
    getSkeleton()->setAnimType(CSK_ANIM_STAND);

  if (mousePresed){
    getSkeleton()->setAnimType(CSK_ANIM_WALK);

    core::vector3df requiredRotation = (pos - node->getAbsolutePosition());
    requiredRotation = requiredRotation.getHorizontalAngle();

    //Doesnt require to point down... so just rotates on Y axis
    requiredRotation.X = 0;
    requiredRotation.Z = 0;

    node->setRotation(requiredRotation);

    anim =	sceneManager->createFlyStraightAnimator(
             node->getPosition(), 
             pos,
             10*pos.getDistanceFrom(node->getPosition()),
             false);

    node->addAnimator(anim);
    anim->drop();
  }

}

scene::ISceneNode* ModelManager::getObjectNodeById(const int id){
  return objects.find(id)->second->getNode();
}

scene::IAnimatedMeshSceneNode* ModelManager::getNpcNodeById(const int id){
  return npcs.find(id)->second->getNode();
}