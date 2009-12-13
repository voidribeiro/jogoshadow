#include "ComponentDialog.h"

ComponentDialog::ComponentDialog():
rectAll(0,0,800,100),
rectText(100,0,700,100)
{
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  windowAll = env->addStaticText(L"", rectAll, false, true, 0, -1, true);

  windowText = env->addStaticText(L"", rectText, false, true, windowAll, -1, true);
  windowText->setBackgroundColor(video::SColor(200,250,250,250));

}

ComponentDialog::~ComponentDialog(){
  if (windowAll)
    windowAll->remove();

}

void ComponentDialog::Draw(){

}

void ComponentDialog::Update(){


}

void ComponentDialog::Say(wchar_t* _message){

  //message = _message;
  //wchar_t * ptr;
  //ptr = wcscat( message, L" BOLINHO");
  windowText->setText(_message);
}

void ComponentDialog::SetPlayerImage(std::string filename){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  playerImage = TextureManager::GetTexture(filename);
  env->addImage(playerImage, core::position2d<s32>(0, 0), true, windowAll);

}

void ComponentDialog::SetNpcImage(std::string filename){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  npcImage = TextureManager::GetTexture(filename);
  env->addImage(playerImage, core::position2d<s32>(0, 0), true, windowAll);

}

void ComponentDialog::SetFont(std::string filename){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  IGUISkin* skin = env->getSkin();
  IGUIFont* font = env->getFont( filename.c_str() ); 

  if (font)
    skin->setFont(font);

  skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
}

void ComponentDialog::SetVisible(bool _visible){
  visible = _visible; 
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

int ComponentDialogBinder::bnd_GetFrom(lua_State* L){
  LuaBinder binder(L); 
  GameObject* gameObject = GameObjectMap::Get(lua_tostring(L,1));
  binder.pushusertype(gameObject->GetComponent(CDIALOG),"ComponentDialog");
  return 1;  
}

int ComponentDialogBinder::bnd_Say(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  std::string  smessage   = lua_tostring(L, 2); 
  std::wstring message    = std::wstring(smessage.begin(), smessage.end());

  componentDialog->Say((wchar_t*)message.c_str());

  return 1;
}

int ComponentDialogBinder::bnd_SetPlayerImage(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  componentDialog->SetPlayerImage( lua_tostring(L, 2) );

  return 1;
}

int ComponentDialogBinder::bnd_SetNpcImage(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  componentDialog->SetNpcImage( lua_tostring(L, 2) );

  return 1;
}

int ComponentDialogBinder::bnd_SetFont(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  componentDialog->SetFont( lua_tostring(L, 2) );

  return 1;
}

int ComponentDialogBinder::bnd_SetVisible(lua_State* L){
  LuaBinder binder(L);

  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  componentDialog->SetVisible( (bool) lua_toboolean(L, 2) );

  return 1;
}