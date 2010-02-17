#include "DeviceManager.h"

DeviceManager::DeviceManager(){
}

DeviceManager::~DeviceManager(){
   soundDevice->drop();
}


/*
   * IrrLicht Main Device
   * instantiates all the engine
   * 
   *	IRRLICHT_API IrrlichtDevice* IRRCALLCONV createDevice(
	 *	  video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,
	 *	  const core::dimension2d<s32>& windowSize = (core::dimension2d<s32>(640,480)),
	 *	  u32 bits = 16,
	 *	  bool fullscreen = false,
	 *	  bool stencilbuffer = false,
	 *	  bool vsync = false,
	 *	  IEventReceiver* receiver = 0);
   */
void DeviceManager::initialize(
      video::E_DRIVER_TYPE deviceType,
		  const core::dimension2d<s32>& windowSize,
		  u32 bits,
		  bool fullscreen,
		  bool stencilbuffer,
		  bool vsync){
  DeviceManager::eventListener = new EventListener();
  DeviceManager::device = createDevice(deviceType, windowSize, bits, fullscreen, stencilbuffer, vsync, eventListener);
  if (device == 0){
    throw 666;
  }
  DeviceManager::driver = device->getVideoDriver();

  soundDevice = createIrrKlangDevice();

  if(!soundDevice)
    printf("Unable to initialize IrrKlang\n");
}

IrrlichtDevice* DeviceManager::device;
video::IVideoDriver* DeviceManager::driver;
EventListener* DeviceManager::eventListener;
ISoundEngine* DeviceManager::soundDevice;

//Not code safe - if not initializated returns null
IrrlichtDevice* DeviceManager::GetDevice(){
  return DeviceManager::device;
}
video::IVideoDriver* DeviceManager::GetDriver(){
  return DeviceManager::driver;
}

