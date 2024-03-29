#include "ComponentGUI.h"

ComponentGUI::ComponentGUI(){

}

ComponentGUI::~ComponentGUI(){

  std::map <std::string, IGUIElement*>::iterator i;

  for( i = elements.begin(); i!=elements.end(); ++i){
    (*i).second->remove();
  }

  elements.clear();
}

void ComponentGUI::Draw(){
}

void ComponentGUI::Update(){
}


void ComponentGUI::addMessageBox(wchar_t* title, wchar_t* message, bool modal){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  env->addMessageBox(title, message, modal);
}

void ComponentGUI::addImageButton(const std::string instancename, const std::string filename, int posX, int posY){
  IrrlichtDevice* device = DeviceManager::GetDevice();
  IGUIEnvironment* env = device->getGUIEnvironment();

  ITexture* tex = TextureManager::GetTexture(filename);

  irr::gui::IGUIButton* buf = env->addButton( core::rect<s32>(posX, posY, 
                                               posX + tex->getOriginalSize().Width + 3,
                                               posY + tex->getOriginalSize().Height + 3) );

  buf->setImage(tex);

  elements[instancename] = buf;

}

bool ComponentGUI::IsButtonPressed(const std::string elementName){
  return ((irr::gui::IGUIButton*)elements[elementName])->isPressed();
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

int ComponentGUIBinder::bnd_GetFrom(lua_State* L){
  LuaBinder binder(L); 
  GameObject* gameObject = GameObjectMap::Get(lua_tostring(L,1));
  binder.pushusertype(gameObject->GetComponent(CGUI),"ComponentGUI");
  return 1;  
}

int ComponentGUIBinder::bnd_AddMessageBox(lua_State* L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");

  std::string  stitle   = lua_tostring(L, 2);
  std::wstring title    = std::wstring(stitle.begin(), stitle.end());

  std::string  smessage = lua_tostring(L, 3);
  std::wstring message  = std::wstring(smessage.begin(), smessage.end());

  bool modal = ( lua_toboolean(L, 4) != 0 ) ;

  componentGUI->addMessageBox( (wchar_t*)title.c_str(), 
                               (wchar_t*)message.c_str(), 
                                modal);

  return 1;
}

int ComponentGUIBinder::bnd_AddImageButton(lua_State *L){
  LuaBinder binder(L);
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");

  std::string instancename  = lua_tostring(L, 2);
  std::string filename      = lua_tostring(L, 3);   
  int posX                  = lua_tointeger(L, 4);
  int posY                  = lua_tointeger(L, 5);

  componentGUI->addImageButton(instancename, filename, posX, posY);

  return 1;
}

int ComponentGUIBinder::bnd_IsButtonPressed(lua_State* L){
  LuaBinder binder(L); 
  ComponentGUI* componentGUI  = (ComponentGUI*) binder.checkusertype(1,"ComponentGUI");
  binder.pushnumber(componentGUI->IsButtonPressed(lua_tostring(L,2)));
  return 1;   
}