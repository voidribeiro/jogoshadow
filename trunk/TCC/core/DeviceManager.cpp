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
  device = createDevice(deviceType, windowSize, bits, fullscreen, stencilbuffer, vsync, receiver);
  if (device == 0){
    throw 666;
  }
  driver = device->getVideoDriver();
}

DeviceManager* DeviceManager::getInstance(){
  if (instance == NULL)
    DeviceManager::instance = new DeviceManager();
  return instance;
}

DeviceManager* DeviceManager::instance;