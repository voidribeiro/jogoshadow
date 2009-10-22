#include "DeviceManager.h"

DeviceManager::DeviceManager(){
}

DeviceManager::~DeviceManager(){
}

void DeviceManager::initialize(
      IEventReceiver* receiver,
      video::E_DRIVER_TYPE deviceType,
		  const core::dimension2d<s32>& windowSize,
		  u32 bits,
		  bool fullscreen,
		  bool stencilbuffer,
		  bool vsync){
  DeviceManager::device = createDevice(deviceType, windowSize, bits, fullscreen, stencilbuffer, vsync, receiver);
  if (device == 0){
    throw 666;
  }
  DeviceManager::driver = device->getVideoDriver();
}

IrrlichtDevice* DeviceManager::device;
video::IVideoDriver* DeviceManager::driver;

//Not code safe - if not initializated returns null
IrrlichtDevice* DeviceManager::GetDevice(){
  return DeviceManager::device;
}
video::IVideoDriver* DeviceManager::GetDriver(){
  return DeviceManager::driver;
}

