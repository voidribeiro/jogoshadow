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
  
//  delete playerImage;
//  delete npcImage;
//  delete message;
//  delete buffer;
} 

void ComponentDialog::Draw(){

}

void ComponentDialog::Update(){


}

void ComponentDialog::Say( const wchar_t* message){
  windowText->setText(message);
  //clearOptions();
}


void ComponentDialog::AddOption(const std::string instanceName, const wchar_t* buttonText, const int x1, const int y1, const int x2, const int y2){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  irr::gui::IGUIElement* buf = env->addButton( core::rect<s32>( x1, y1, x2, y2 ), 
                                               windowOptions, -1, buttonText );

  options[instanceName] = buf;

}

void ComponentDialog::AddImageOption( const std::string instanceName, const std::string filename, const int posX, const int posY){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  ITexture* tex = TextureManager::GetTexture(filename);

  irr::gui::IGUIButton* buf = env->addButton( core::rect<s32>(posX, posY, 
                                               posX + tex->getOriginalSize().Width + 3,
                                               posY + tex->getOriginalSize().Height + 3), 
                                               windowOptions );
  buf->setImage(tex);
 
  options[instanceName] = buf;
}

bool ComponentDialog::IsButtonPressed(const std::string instanceName){
  if(options[instanceName] == NULL)
    return false;  

  return ((irr::gui::IGUIButton*)options[instanceName])->isPressed();
}

void ComponentDialog::ClearOptions(){
  map<std::string, IGUIElement*>::iterator it;

  for ( it = options.begin() ; it != options.end(); it++ ){
   if(it->second != NULL){
     it->second->remove();
     it->second = NULL;
   }
  }

  options.clear();
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

  int x1 = lua_tointeger(L, 4);
  int y1 = lua_tointeger(L, 5);
  int x2 = lua_tointeger(L, 6);
  int y2 = lua_tointeger(L, 7);

  componentDialog->AddOption(instanceName, (wchar_t*)buttonText.c_str(), x1, y1, x2, y2);

  return 1;
}

int ComponentDialogBinder::bnd_AddImageOption(lua_State *L){
  LuaBinder binder(L);
  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");

  std::string instanceName  = lua_tostring(L, 2);
  
  std::string filename = lua_tostring(L, 3);
  
  int x = lua_tointeger(L, 4);
  int y = lua_tointeger(L, 5);

  componentDialog->AddImageOption(instanceName, filename, x, y);

  return 1;
}

int ComponentDialogBinder::bnd_IsButtonPressed(lua_State* L){
  LuaBinder binder(L); 
  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  binder.pushnumber(componentDialog->IsButtonPressed(lua_tostring(L,2)));
  return 1;   
}
 
int ComponentDialogBinder::bnd_ClearOptions(lua_State* L){
  LuaBinder binder(L); 
  ComponentDialog* componentDialog  = (ComponentDialog*) binder.checkusertype(1,"ComponentDialog");
  
  componentDialog->ClearOptions();

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
  componentDialog->SetVisible( ( lua_toboolean(L, 2) != 0 ) );

  return 1;
}