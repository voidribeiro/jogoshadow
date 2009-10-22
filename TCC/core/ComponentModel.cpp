#include "ComponentModel.h"

ComponentModel::ComponentModel(const std::string filename){

  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver(); 
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  mesh = sceneManager->getMesh( filename.c_str() );

  if(!mesh)
    printf("DEU PAU!");

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