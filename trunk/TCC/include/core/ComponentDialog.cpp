#include "ComponentDialog.h"

ComponentDialog::ComponentDialog(){
}

ComponentDialog::~ComponentDialog(){
  if (window)
    window->remove();

}

void ComponentDialog::Draw(){

}

void ComponentDialog::Update(){

}

void ComponentDialog::Say( std::string imageFile, wchar_t* message, std::string fontFile ){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  /* imagem */
  ITexture* tex = TextureManager::GetTexture(imageFile);
  env->addImage(tex, core::position2d<s32>(0, 0));

  /* fala */ 
  core::rect<s32> quadrado(100,0,800,100);
  window = env->addStaticText(message, quadrado,false, true, 0, -1, true);
  window->setBackgroundColor(video::SColor(200,250,250,250));

  /* fonte */
  IGUISkin* skin = env->getSkin();
  IGUIFont* font = env->getFont( fontFile.c_str() ); 

  if (font)
    skin->setFont(font);

  skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);

  
}

/////////////////////////////////////////////////////////

int ComponentDialogBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentDialog",0,componentDialogFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentDialogBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentDialogBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentDialog* componentDialog = new ComponentDialog();
  binder.pushusertype(componentDialog,"ComponentDialog");
  return 1;
}

int ComponentDialogBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentDialog);

  return 1;
}

int ComponentDialogBinder::bnd_Say(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  std::string  imageFile   = lua_tostring(L, 2); 

  std::string  smessage   = lua_tostring(L, 3); 
  std::wstring message    = std::wstring(smessage.begin(), smessage.end());

  std::string  fontFile   = lua_tostring(L, 4); 

  componentDialog->Say(imageFile, (wchar_t*)message.c_str(), fontFile);

  return 1;
}