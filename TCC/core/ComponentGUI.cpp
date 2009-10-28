#include "ComponentGUI.h"

ComponentGUI::ComponentGUI(){

}

ComponentGUI::~ComponentGUI(){

}

void ComponentGUI::Draw(){
  elem->draw();
  //printf("%d", elem->getChildren().getSize());
}

void ComponentGUI::Update(){

}


void ComponentGUI::addMessageBox(wchar_t* title, wchar_t* message, bool modal){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  env->addMessageBox(title, message, true);

}

void ComponentGUI::addImage(const std::string filename, int posX, int posY){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  //IGUIImage* img = env->addImage(texture, irr::core::position2d);

  elem = env->addButton( core::rect<s32>(250,250,500,400), 0, 666 );

  //adicina o parent na imagem
  env->addImage(TextureManager::GetTexture(filename), 
                core::position2d<s32>(0, 0),
                true, elem, 5 );
}



wchar_t* ComponentGUI::convertStrToWChar(std::string text)
{
	const char *tempChar = text.c_str();
	size_t origsize = strlen(tempChar) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, tempChar, _TRUNCATE);
	wcscat_s(wcstring, L"(wchar_t *)");
	return wcstring;
}

/////////////////////////////////////////////////////////

int ComponentGUIBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentGUI",0,componentGUIFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentGUIBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentGUIBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI = new ComponentGUI();
  binder.pushusertype(componentGUI,"ComponentGUI");
  return 1;
}

int ComponentGUIBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentGUI);
  return 1;
}

int ComponentGUIBinder::bnd_AddMessageBox(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");

  wchar_t* text = L"b o l i n h o ";

  //text = componentGUI->convertStrToWChar( text );

  //está fixo porque eu não sei converter de string pra wchar_t*
  componentGUI->addMessageBox(text, 
                              text, 
                              true);

  return 1;
}

int ComponentGUIBinder::bnd_AddImage(lua_State *L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");

  std::string text = lua_tostring(L, 2);
  int posX         = lua_tointeger(L, 3);
  int posY         = lua_tointeger(L, 4);

  componentGUI->addImage(text, posX, posY);

  return 1;
}