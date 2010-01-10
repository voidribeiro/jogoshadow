#include "ComponentDialog.h"

ComponentDialog::ComponentDialog():
rectAll(0,0,800,100),
rectText(64,0,736,64),
rectOptions(64,64,736,100)
{
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  windowAll = env->addStaticText(L"", rectAll, false, true, 0, -1, true);

  windowText = env->addStaticText(L"", rectText, false, true, windowAll, -1, true);
  windowText->setBackgroundColor(video::SColor(200,250,250,250));

  windowOptions = env->addStaticText(L"", rectOptions, false, true, windowAll, -1, true);
  windowOptions->setBackgroundColor(video::SColor(200,200,200,200));

}

ComponentDialog::~ComponentDialog(){
  if (windowAll)
    windowAll->remove();

}

void ComponentDialog::Draw(){

}

void ComponentDialog::Update(){


}

void ComponentDialog::Say(wchar_t* message){
  windowText->setText(message);
  clearOptions();
}


void ComponentDialog::AddOption(std::string instanceName, wchar_t* buttonText, int posX, int posY){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  irr::gui::IGUIElement* buf = env->addButton( core::rect<s32>(posX, posY, 
                                               posX + 150,
                                               posY + 25 ), 
                                               windowOptions, -1, buttonText );

  options[instanceName] = buf;

}

bool ComponentDialog::IsButtonPressed(const std::string instanceName){
  return ((irr::gui::IGUIButton*)options[instanceName])->isPressed();
}   

void ComponentDialog::clearOptions(){
/*  while (options.size != 0){
    AbstractComponent* c = (*options.begin());
    options.pop_front();
    if (c != NULL){
      delete c;
      c = NULL;
    }
  }
*/
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
  env->addImage(playerImage, core::position2d<s32>(736, 0), true, windowAll);

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

void ComponentDialog::SetVisible(bool visible){
  windowAll->setVisible(visible);
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

int ComponentDialogBinder::bnd_AddOption(lua_State *L){
  LuaBinder binder(L);
  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  std::string instanceName  = lua_tostring(L, 2);
  
  std::string  buf = lua_tostring(L, 3);
  std::wstring buttonText    = std::wstring( buf.begin(), buf.end() );

  int posX = lua_tointeger(L, 4);
  int posY = lua_tointeger(L, 5);

  componentDialog->AddOption(instanceName, (wchar_t*)buttonText.c_str(), posX, posY);

  return 1;
}

int ComponentDialogBinder::bnd_IsButtonPressed(lua_State* L){
  LuaBinder binder(L); 
  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  binder.pushnumber(componentDialog->IsButtonPressed(lua_tostring(L,2)));
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