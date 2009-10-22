#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__

#include <irrlicht.h>
#include <exception>

using namespace irr;
using namespace std;

class DeviceManager{
  private:
    static IrrlichtDevice* device;
    static video::IVideoDriver* driver;

  public:
    explicit DeviceManager ();
    virtual ~DeviceManager();

    //Parameters from irrlicht create device (modified defaults)
    static void initialize(
      IEventReceiver* receiver = 0,
      video::E_DRIVER_TYPE deviceType = video::EDT_DIRECT3D9,
		  // parantheses are necessary for some compilers
      const core::dimension2d<s32>& windowSize = (core::dimension2d<s32>(800,600)),
      u32 bits = 32,
      bool fullscreen = false,
		  bool stencilbuffer = false,
		  bool vsync = true);

    static IrrlichtDevice* GetDevice();
    static video::IVideoDriver* GetDriver();
};

#endif