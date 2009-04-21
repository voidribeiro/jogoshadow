#include "GUIManager.h"

GUIManager::GUIManager(){}

GUIManager::GUIManager(IGUIEnvironment* env){
  IGUISkin* skin;
  IGUIFont* font;

  this->env = env;

  skin = env->getSkin();
	font = env->getFont("resources/fonthaettenschweiler.bmp");

  if (font)
		skin->setFont(font);

  this->env->addMessageBox(L"Teste com GUI", L"Esta janela toma o controle do input, basta fecha-la para usar a câmera normalmente", true);
}

GUIManager::~GUIManager(){

}

void GUIManager::update(){
  
}

void GUIManager::drawAll(){
  env->drawAll();
}