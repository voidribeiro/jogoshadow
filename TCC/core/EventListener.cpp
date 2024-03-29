#include "EventListener.h"

EventListener::EventListener(){}

EventListener::~EventListener(){
  keysPressed.clear();
  //delete guiManager;
}

/*
 * KEY EVENTS
 */
 
void EventListener::pushKeyEvent( EKEY_CODE code ){
  keysPressed.insert( std::pair< EKEY_CODE,bool >( code,false ) );
}

void EventListener::popKeyEvent( EKEY_CODE code ){
  std::map < EKEY_CODE, bool>::iterator it;
  it = keysPressed.find(code);
  keysPressed.erase(it);
}

bool EventListener::isPressed( EKEY_CODE code ){
  return keysPressed.find(code)->second;
}

bool EventListener::OnEvent(const SEvent &event){

  //KEY Event Variables
  bool pressed;
  EKEY_CODE code;

  //GUI Event Variables
  s32 id;
  gui::EGUI_EVENT_TYPE eventType;

  switch (event.EventType){

    case EET_MOUSE_INPUT_EVENT:

      MouseState.pos = irr::core::position2di(event.MouseInput.X, event.MouseInput.Y);

			//mouseDeltaX = event.MouseInput.X - mouseX;
			//mouseDeltaY = event.MouseInput.Y - mouseY;

      switch(event.MouseInput.Event){
	      case EMIE_LMOUSE_PRESSED_DOWN:
		      MouseState.LeftButtonDown = true;
		      break;

	      case EMIE_LMOUSE_LEFT_UP:
		      MouseState.LeftButtonDown = false;
		      break;

	      case EMIE_RMOUSE_PRESSED_DOWN:
		      MouseState.RightButtonDown = true;
		      break;

	      case EMIE_RMOUSE_LEFT_UP:
		      MouseState.RightButtonDown = false;
		      break;

      }

      break;

    case EET_KEY_INPUT_EVENT:

      //quando um evento de KEY_INPUT aconte�e a tecla muda o status de true ou false
      code    = event.KeyInput.Key;
      pressed = event.KeyInput.PressedDown;

      if(keysPressed.find(code) == keysPressed.end())
        pushKeyEvent(code);

      keysPressed.find(code)->second = pressed;
      //printf("%d",keysPressed.find(code)->second);

      break;

    case EET_GUI_EVENT:
      id        = event.GUIEvent.Caller->getID();
      eventType = event.GUIEvent.EventType;

      //printf("Evento de GUI\n");

      break;

  }

	return false;
}
