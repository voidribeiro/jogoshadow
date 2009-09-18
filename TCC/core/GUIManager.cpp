#include "GUIManager.h"

GUIManager::GUIManager(){}

GUIManager::GUIManager(IGUIEnvironment* _env, IVideoDriver* _driver){

  IGUISkin* skin;
  IGUIFont* font;

  env     = _env;
  driver  = _driver;

  /*
   * This font file was generated by the IrrLicht Font Generator =)
   */
  skin = env->getSkin();
	font = env->getFont("resources/verdana.png");

  if (font)
		skin->setFont(font);

	gui::IGUIToolBar* bar = env->addToolBar();

  video::ITexture* image = driver->getTexture("resources/open.png");
	bar->addButton(1001, 0, L"Open a model", image, 0, false, true);

	image = driver->getTexture("resources/tools.png");
	bar->addButton(1002, 0, L"Open Toolset",image, 0, false, true);

	image = driver->getTexture("resources/zip.png");
	bar->addButton(1003, 0, L"Set Model Archive",image, 0, false, true);

	image = driver->getTexture("resources/help.png");
	bar->addButton(1004, 0, L"Open Help", image, 0, false, true);

  env->addMessageBox(L"Teste com GUI", L"Esta janela toma o controle do input, basta fecha-la para usar a c�mera normalmente", true);

}

GUIManager::~GUIManager(){

}

void GUIManager::update(){
  
}

void GUIManager::drawAll(){
  env->drawAll();
}

void GUIManager::processEventCallback(EGUI_EVENT_TYPE type, const int id){
  //  printf("Evento na GUI!\n");
}