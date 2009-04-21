#include "SoundManager.h"

SoundManager::SoundManager(){
}

SoundManager::~SoundManager(){
  soundDevice->drop(); // delete device
}

bool SoundManager::init(){
  soundDevice = createIrrKlangDevice();

  if(!soundDevice)
    return false;
  else
    return true;
}

void SoundManager::playSound( char* filename, bool loop ){
  soundDevice->play2D(filename, true);
}