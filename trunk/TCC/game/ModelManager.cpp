#include "ModelManager.h"

ModelManager::ModelManager(irr::scene::ISceneManager* sm){
  sceneManager = sm;
}

ModelManager::~ModelManager(){
 models.clear();
}

void ModelManager::pushModel(const char *filename, int modelType){
  std::map <int, Model*>::iterator modelIt = models.end();
  
  Model* model;
  scene::IAnimatedMesh* mesh;
  scene::ISceneNode* node;

  mesh = sceneManager->getMesh( filename );

  
  //se não conseguir criar a mesh retorna
  if(!mesh)
    return;

  //cria o node baseado no parâmetro modelType
  switch(modelType){
    case HERO_MODEL:
      node = sceneManager->addAnimatedMeshSceneNode( mesh );
      break;

    case NPC_MODEL:
      node = sceneManager->addAnimatedMeshSceneNode( mesh );
      break;

    case SCENARIO_MODEL:
      node = sceneManager->addOctTreeSceneNode( mesh );
      break;

    case OBJECT_MODEL:
      node = sceneManager->addMeshSceneNode( mesh );
      break;
  }
  

  model = new Model( (int) models.size(), modelType, mesh, node);

  models.insert(modelIt, pair<int, Model*>( (int) models.size(), model ));

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

  //altera a escala do node
  models.find(0)->second->getNode()->setScale( irr::core::vector3df(1,1,2) );
}