#ifndef _EVENTLISTENER_H_
#define _EVENTLISTENER_H_

/*

Name: EventListener.h

Description:
This is used to report to the application when and what event happened, and use that information to
affect the whole application

*/


#include <map>
#include "../include/irrlicht.h"

using namespace irr;

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
    std::map <EKEY_CODE, bool> keysPressed;
    std::map <int, gui::EGUI_EVENT_TYPE> guiEvents;

    // We'll create a struct to record info on the mouse state
	  struct SMouseState{
      irr::core::position2di pos;
		  bool LeftButtonDown;
		  SMouseState() : LeftButtonDown(false) { }
	  } MouseState;

	public:

    EventListener();
    ~EventListener();

    void pushKeyEvent(EKEY_CODE code);
    void popKeyEvent(EKEY_CODE code);

    void pushGUIEvent(gui::EGUI_EVENT_TYPE type, int id);
    void popGUIEvent(gui::EGUI_EVENT_TYPE type, int id);

    /*
     * Retrieves the current key state (pressed/ not pressed)
     */
    bool isPressed(EKEY_CODE code);

    /*
     * [TODO] GUI Event callbacks
     * Processes all the events
     */
    virtual bool OnEvent(const SEvent& event);

    const SMouseState &GetMouseState(void) const{
		  return MouseState;
	  }

};

#endif