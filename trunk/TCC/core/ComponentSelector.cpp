#include "ComponentSelector.h"

ComponentSelector::ComponentSelector(){
  selector = NULL;
}

ComponentSelector::~ComponentSelector(){
}

void ComponentSelector::Draw(){
  //TODO - This is only for test. Remove this
  /*
  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  ISceneManager* sceneManager = DeviceManager::GetDevice()->getSceneManager();

	//core::line3d<f32> line;
  core::line3d<f32> line = sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates( DeviceManager::eventListener->GetMouseState().pos , sceneManager->getActiveCamera() ); 

	//line.start = camera->getPosition();
	//line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;

	core::vector3df intersection;
  core::triangle3df tri;

  if (sceneManager->getSceneCollisionManager()->getCollisionPoint(
		line, selector, intersection, tri)){

    driver->draw3DTriangle(tri, video::SColor(255,255,0,0));
  }
  */
}

void ComponentSelector::SetParent(GameObject* parent){
  AbstractComponent::SetParent(parent);
}

void ComponentSelector::CreateSelector(){

  ComponentModel* cModel = (ComponentModel*)parent->GetComponent(CMODEL);
  if (cModel == NULL){
    printf("Missing Model Reference\n");
    return;
  }

  ISceneManager* sceneManager = DeviceManager::GetDevice()->getSceneManager();
  this->selector = sceneManager->createOctTreeTriangleSelector(cModel->GetMeshRef(), cModel->GetNodeRef());
}

void ComponentSelector::CheckSelector(){
  if(selector == NULL)
    CreateSelector();
}

float ComponentSelector::GetDistanceFromMouse(irr::core::position2d<s32> mousePosition){
  CheckSelector();
  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  ISceneManager* sceneManager = DeviceManager::GetDevice()->getSceneManager();

  core::line3d<f32> line = sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(mousePosition, sceneManager->getActiveCamera()); 
	core::vector3df intersection;
  core::triangle3df tri;

  if (sceneManager->getSceneCollisionManager()->getCollisionPoint(
		line, selector, intersection, tri)){
      return intersection.getDistanceFrom(sceneManager->getActiveCamera()->getPosition());
  }
  return -1;
}

irr::core::vector3df ComponentSelector::GetCollisionPoint(irr::core::position2d<s32> mousePosition){

  CheckSelector();
  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver();
  ISceneManager* sceneManager = DeviceManager::GetDevice()->getSceneManager();

  core::line3d<f32> line = sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(mousePosition, sceneManager->getActiveCamera()); 
	core::vector3df intersection;
  core::triangle3df tri;
  
  sceneManager->getSceneCollisionManager()->getCollisionPoint(line, selector, intersection, tri);
    
  return intersection;
}

/////////////////////////////////////////////////////////

int ComponentSelectorBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentSelector",0,componentSelectorFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentSelectorBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentSelectorBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L); 
  ComponentSelector* componentSelector = new ComponentSelector();
  binder.pushusertype(componentSelector,"ComponentSelector");
  return 1;
}

int ComponentSelectorBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentSelector* componentSelector  = (ComponentSelector*) binder.checkusertype(1,"ComponentSelector");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentSelector);
  //componentSelector->CheckSelector();
  return 1;
}

int ComponentSelectorBinder::bnd_GetCollisionPoint(lua_State* L){
  LuaBinder binder(L);
  ComponentSelector* componentSelector  = (ComponentSelector*) binder.checkusertype(1,"ComponentSelector");

  irr::core::position2di mousePos;
  irr::core::vector3df intersection;

  irr::s32 x = (irr::s32)lua_tonumber(L,2);
  irr::s32 y = (irr::s32)lua_tonumber(L,3);

  mousePos = irr::core::position2di( x, y);
  
  intersection = componentSelector->GetCollisionPoint(mousePos);

  binder.pushnumber(intersection.X);
  binder.pushnumber(intersection.Y);
  binder.pushnumber(intersection.Z);
  
  return 3;
}

int ComponentSelectorBinder::bnd_GetFrom(lua_State* L){
  LuaBinder binder(L); 
  GameObject* gameObject = GameObjectMap::Get(lua_tostring(L,1));
  binder.pushusertype(gameObject->GetComponent(CSELECTOR),"ComponentSelector");
  return 1;  
}