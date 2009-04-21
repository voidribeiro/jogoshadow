#ifndef _GUIMANAGER_H_
#define _GUIMANAGER_H_

#include "../include/irrlicht.h"

using namespace irr;
using namespace gui;

class GUIManager{

  private:
    IGUIEnvironment* env;

  public:
    GUIManager();
    GUIManager(IGUIEnvironment* env);
    ~GUIManager();
    
    void update();
    void drawAll();

};

#endif