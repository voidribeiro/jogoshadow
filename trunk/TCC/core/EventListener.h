#ifndef _EVENTLISTENER_H_
#define _EVENTLISTENER_H_

#include "../include/irrlicht.h"

//IrrLicht namescpaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventListener : public IEventReceiver
{

	public:

    // We'll create a struct to record info on the mouse state
	  struct SMouseState{
		  core::position2di pos;
		  bool LeftButtonDown;
		  SMouseState() : LeftButtonDown(false) { }
	  } MouseState;

    EventListener(){}

	  // This is the one method that we have to implement
	  virtual bool OnEvent(const SEvent& event){

		  // Remember the mouse state
      if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
			  switch(event.MouseInput.Event){
			    case EMIE_LMOUSE_PRESSED_DOWN:
				    MouseState.LeftButtonDown = true;
				    break;

			    case EMIE_LMOUSE_LEFT_UP:
				    MouseState.LeftButtonDown = false;
				    break;
		    }
		  }
		  return false;
	  }

    const SMouseState & GetMouseState(void) const{
		  return MouseState;
	  }

};

#endif //_EVENTLISTENER_H_