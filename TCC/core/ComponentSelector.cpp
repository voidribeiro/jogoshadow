#include "ComponentSelector.h"

ComponentSelector::ComponentSelector(){
  selector = NULL;
}

ComponentSelector::~ComponentSelector(){
}

void ComponentSelector::Draw(){
  //TODO - This is only for test. Remove this
  
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

scene::ITriangleSelector* ComponentSelector::GetSelector(){
  if(selector == NULL)
    CreateSelector();
  return selector;
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
  componentSelector->GetSelector();
  return 1;
}