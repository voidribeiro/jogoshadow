#include "ModelManager.h"

ModelManager::ModelManager(irr::scene::ISceneManager* sm){
  sceneManager = sm;
}

ModelManager::~ModelManager(){
 objects.clear();
 npcs.clear();
}

void ModelManager::pushModel(const char *filename, int modelType){
  scene::IAnimatedMesh* mesh;

  scene::ISceneNode* scenarioNode;
  scene::IAnimatedMeshSceneNode* animatedNode;
  scene::IMeshSceneNode* staticNode;

  std::map <int, ObjectModel*>::iterator objIt = objects.end();
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();

  NpcModel* npc;
  ObjectModel* obj;

  mesh = sceneManager->getMesh( filename );
  
  //se não conseguir criar a mesh retorna
  if(!mesh)
    return;

  //cria o node baseado no parâmetro modelType
  switch(modelType){
    case HERO_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );
      hero = new HeroModel(1, HERO_MODEL, mesh, animatedNode);
      break;

    case SCENARIO_MODEL:
      scenarioNode = sceneManager->addOctTreeSceneNode( mesh );

      scenario = new ScenarioModel(2, SCENARIO_MODEL, mesh, scenarioNode);
      break;

    case NPC_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

      npc = new NpcModel( (int)npcs.size(), NPC_MODEL, mesh, animatedNode);
      npcs.insert(npcIt, pair<int, NpcModel*>( (int)npcs.size(), npc) );

      getNpcNodeById( 0 )->setMD2Animation(scene::EMAT_RUN);
      break;

    case OBJECT_MODEL:
      staticNode = sceneManager->addMeshSceneNode( mesh );

      obj = new ObjectModel( (int)objects.size(), OBJECT_MODEL, mesh, staticNode);
      objects.insert(objIt, pair<int, ObjectModel*>( (int)objects.size(), obj) );
      break;
  }

}

void ModelManager::pushModel(const char *filename, int modelType, ITexture* texture){
  scene::IAnimatedMesh* mesh;

  scene::IAnimatedMeshSceneNode* animatedNode;

  std::map <int, ObjectModel*>::iterator objIt = objects.end();
  std::map <int, NpcModel*>::iterator npcIt = npcs.end();

  NpcModel* npc;

  mesh = sceneManager->getMesh( filename );
  
  //se não conseguir criar a mesh retorna
  if(!mesh)
    return;

  //cria o node baseado no parâmetro modelType
  switch(modelType){
    case NPC_MODEL:
      animatedNode = sceneManager->addAnimatedMeshSceneNode( mesh );

      npc = new NpcModel( (int)npcs.size(), NPC_MODEL, mesh, animatedNode, texture);
      npcs.insert(npcIt, pair<int, NpcModel*>( (int)npcs.size(), npc) );

      getNpcNodeById( 0 )->setMD2Animation(scene::EMAT_STAND);
      break;

  }

}


void ModelManager::popModel(){
  // TODO
  // meus testes pra desregistrar um mesh e um node estão resultando em erros grotescos de execução
}

void ModelManager::update(){
  //ainda está hardcode, mas o ModelManager tem um update próprio pra atualizar os nodes 
  //isso é interessante porque é possível adicionar por exemplo um processamento de física separado do GameManager
  //pode-se alterar diretamente o map de nós
  //outra coisa é que este update estando separado, ele pode rodar um número de vezes diferente do gameManager principal

  //altera a escala do cenário
  scenario->getNode()->setScale( irr::core::vector3df(1,1,2) );
  
  //altera a posição do MD2
  getNpcNodeById(0)->setPosition(irr::core::vector3df(0,30,0));
}

scene::ISceneNode* ModelManager::getObjectNodeById(int id){
  return objects.find(id)->second->getNode();
}

scene::IAnimatedMeshSceneNode* ModelManager::getNpcNodeById(int id){
  return npcs.find(id)->second->getNode();
}