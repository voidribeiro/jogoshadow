#include "EventListener.h"

EventListener::EventListener(){}

EventListener::~EventListener(){
  keysPressed.clear();
}

void EventListener::pushKeyEvent(irr::EKEY_CODE code){
  keysPressed.insert( std::pair<irr::EKEY_CODE,bool>(code,false) );
}

void EventListener::popKeyEvent(irr::EKEY_CODE code){
  it = keysPressed.find(code);
  keysPressed.erase(it);
}

bool EventListener::isPressed(irr::EKEY_CODE code){
  return keysPressed.find(code)->second;
}


bool EventListener::OnEvent(const irr::SEvent &event){

	  // Remember the mouse state
    switch (event.EventType){
      case irr::EET_MOUSE_INPUT_EVENT:

        switch(event.MouseInput.Event){
		      case irr::EMIE_LMOUSE_PRESSED_DOWN:
			      MouseState.LeftButtonDown = true;
			      break;

		      case irr::EMIE_LMOUSE_LEFT_UP:
			      MouseState.LeftButtonDown = false;
			      break;

        }

        break;

      case irr::EET_KEY_INPUT_EVENT:

        //quando um evento de KEY_INPUT aconteçe a tecla muda o status de true ou false
        irr::EKEY_CODE code = event.KeyInput.Key;
        bool pressed = event.KeyInput.PressedDown;

        if(keysPressed.find(code) == keysPressed.end())
          pushKeyEvent(code);

        keysPressed.find(code)->second = pressed;
        //printf("%d",keysPressed.find(code)->second);

        break;

    }

  	return false;
}
