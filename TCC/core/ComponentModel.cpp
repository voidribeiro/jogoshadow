#include "ComponentModel.h"

ComponentModel::ComponentModel(const std::string filename){

  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver(); 
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  mesh = sceneManager->getMesh( filename.c_str() );

  if(!mesh)
    printf("Unable to load mesh!");
 
  node = sceneManager->addAnimatedMeshSceneNode( mesh );
}

ComponentModel::~ComponentModel(){
  if (node)
    node->remove();
  node = 0;

  if (mesh)
    mesh->drop();
	mesh = 0;
}

void ComponentModel::Draw(){

}

void ComponentModel::setMaterial(irr::video::SMaterial material){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  node->getMaterial(0) = material;

  //ficou porco mas é só pra testar!!!
  node->setMD2Animation(scene::EMAT_STAND);
  node->setAnimationSpeed(60); 
}

void ComponentModel::SetParent(GameObject* parent){
  AbstractComponent::SetParent(parent);
  parent->AddChildNode(node);
}

IAnimatedMesh* ComponentModel::GetMeshRef(){
  return mesh;
}

IAnimatedMeshSceneNode* ComponentModel::GetNodeRef(){
  return node;
}

/////////////////////////////////////////////////////////

int ComponentModelBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentModel",0,componentModelFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentModelBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentModelBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentModel* componentModel = new ComponentModel(lua_tostring(L,1));
  binder.pushusertype(componentModel,"ComponentModel");
  return 1;
}

int ComponentModelBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentModel* componentModel  = (ComponentModel*) binder.checkusertype(1,"ComponentModel");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentModel);
  return 1;
}

int ComponentModelBinder::bnd_SetTexture(lua_State* L){
  LuaBinder binder(L);
  ComponentModel* componentModel  = (ComponentModel*) binder.checkusertype(1,"ComponentModel");

  std::string textureName = lua_tostring(L, 2);

  video::SMaterial material;

	material.setTexture(0, TextureManager::GetTexture(textureName) );
	//material.Lighting = false;

  componentModel->setMaterial(material);

  return 1;
}