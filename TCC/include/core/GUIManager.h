#ifndef _GUIMANAGER_H_
#define _GUIMANAGER_H_

/*

Name: GUIManager.h

Description:
This class is used to manage all the creation of the GUI interfaces and to process the event callbacks 
referenced to GUI, sent by the eventListener

*/

#include "irrlicht.h"

using namespace irr;
using namespace gui;

class GUIManager{

  private:
     /*
      * This class requires a pointer to the main IGUIEnviroment to create and manage the GUI
      */
    IGUIEnvironment* env;

  public:
    GUIManager();
    GUIManager(IGUIEnvironment* env);
    ~GUIManager();
    
    void update();
    void drawAll();

     /*
      * When a GUI event happen, the EventListener will call this function
      * The EGUI_EVENT_TYPE is passed by IrrLicht, the id is the unique ID of the GUI element
      */
    void processEventCallback(EGUI_EVENT_TYPE type, int id);

};

#endif