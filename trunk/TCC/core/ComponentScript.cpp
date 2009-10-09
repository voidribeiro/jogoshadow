#include "ComponentScript.h"

ComponentScript::ComponentScript(GameObject* parent):AbstractComponent(parent){
}

ComponentScript::~ComponentScript(){
}

int ComponentScript::GetType(){
  return CSCRIPT;
}