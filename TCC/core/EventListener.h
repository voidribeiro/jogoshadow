#ifndef _EVENTLISTENER_H_
#define _EVENTLISTENER_H_

#include <map>
#include "../include/irrlicht.h"

class EventListener : public irr::IEventReceiver{
  private: 
    /* 
     * The keysPressed map is composed by the keys from the IrrLicht Enum and a boolean
     * representing if the key is pressed or not. This map observes only the KEYS referenced 
     * by the pushKeyEvent() function.
     *
     * keycodes in http://irrlicht.sourceforge.net/docu/_keycodes_8h-source.html 
     *
     */
    std::map <irr::EKEY_CODE, bool> keysPressed;
    std::map <irr::EKEY_CODE, bool>::iterator it;

    // We'll create a struct to record info on the mouse state
	  struct SMouseState{
      irr::core::position2di pos;
		  bool LeftButtonDown;
		  SMouseState() : LeftButtonDown(false) { }
	  } MouseState;

	public:

    EventListener();
    ~EventListener();

    void pushKeyEvent(irr::EKEY_CODE code);
    void popKeyEvent(irr::EKEY_CODE code);

    // retrieves the current key state (pressed/ not pressed)
    bool isPressed(irr::EKEY_CODE code);

	  // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event);

    const SMouseState &GetMouseState(void) const{
		  return MouseState;
	  }

};

#endif //_EVENTLISTENER_H_