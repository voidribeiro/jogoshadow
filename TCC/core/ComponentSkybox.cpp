#include "ComponentSkybox.h"

ComponentSkybox::ComponentSkybox( const std::string _upTexture,
                                  const std::string _dnTexture,
                                  const std::string _lfTexture,
                                  const std::string _rtTexture,
                                  const std::string _ftTexture,
                                  const std::string _bkTexture)
{

  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver(); 
  
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  sceneManager->addSkyBoxSceneNode(
        TextureManager::GetTexture(_upTexture),
				TextureManager::GetTexture(_dnTexture),
				TextureManager::GetTexture(_lfTexture),
				TextureManager::GetTexture(_rtTexture),
				TextureManager::GetTexture(_ftTexture),
				TextureManager::GetTexture(_bkTexture));

}

ComponentSkybox::~ComponentSkybox(){
  //TODO - Remover o skybox
}

void ComponentSkybox::Draw(){
  // DESENHAR usando algo diferente do DrawAll()
}


/////////////////////////////////////////////////////////

int ComponentSkyboxBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentSkybox",0,ComponentSkyboxFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentSkyboxBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentSkyboxBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentSkybox* componentSkybox = new ComponentSkybox(lua_tostring(L,1),
                                                         lua_tostring(L,2),
                                                         lua_tostring(L,3),
                                                         lua_tostring(L,4),
                                                         lua_tostring(L,5),
                                                         lua_tostring(L,6));

  binder.pushusertype(componentSkybox,"ComponentSkybox");
  return 1;
}

int ComponentSkyboxBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentSkybox* componentSkybox  = (ComponentSkybox*) binder.checkusertype(1,"ComponentSkybox");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentSkybox);
  return 1;
}