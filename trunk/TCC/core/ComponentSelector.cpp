#include "ComponentSelector.h"

ComponentSelector::ComponentSelector(){
}

ComponentSelector::~ComponentSelector(){
}

void ComponentSelector::Draw(){

}

void ComponentSelector::SetParent(GameObject* parent){
  AbstractComponent::SetParent(parent);
}

void ComponentSelector::SetComponentModelReference(ComponentModel* cModelRef){
  this->cModel = cModelRef;
  CreateSelector();
}

void ComponentSelector::CreateSelector(){
  ISceneManager* sceneManager = DeviceManager::GetDevice()->getSceneManager();
  this->selector = sceneManager->createOctTreeTriangleSelector(cModel->GetMeshRef(), cModel->GetNodeRef());
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
  ComponentModel* cModelReference = (ComponentModel*)gameObject->GetComponent(CMODEL);
  if (cModelReference == NULL){
    delete(componentSelector);
    componentSelector = NULL;
    return 1;
  }
  componentSelector->SetComponentModelReference(cModelReference);
  gameObject->AddComponent(componentSelector);
  return 1;
}