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

  
  //se n�o conseguir criar a mesh retorna
  if(!mesh)
    return;

  //cria o node baseado no par�metro modelType
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
  // meus testes pra desregistrar um mesh e um node est�o resultando em erros grotescos de execu��o
}

void ModelManager::update(){
  //ainda est� hardcode, mas o ModelManager tem um update pr�prio pra atualizar os nodes 
  //isso � interessante porque � poss�vel adicionar por exemplo um processamento de f�sica separado do GameManager
  //pode-se alterar diretamente o map de n�s
  //outra coisa � que este update estando separado, ele pode rodar um n�mero de vezes diferente do gameManager principal

  //altera a escala do node
  models.find(0)->second->getNode()->setScale( irr::core::vector3df(1,1,2) );
}