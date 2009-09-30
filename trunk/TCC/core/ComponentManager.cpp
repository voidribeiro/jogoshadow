#include "ComponentManager.h"

ComponentManager::ComponentManager(){
}

ComponentManager::~ComponentManager(){
}

void ComponentManager::initialize(
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

ComponentManager* ComponentManager::getInstance(){
  return instance;
}