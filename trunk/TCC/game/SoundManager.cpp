#include "SoundManager.h"

SoundManager::SoundManager(){
}

/*
 * Destroys the main sound device
 */
SoundManager::~SoundManager(){
  soundDevice->drop();
}

bool SoundManager::init(){
  soundDevice = createIrrKlangDevice();

  if(!soundDevice)
    return false;
  else
    return true;
}

void SoundManager::playSound( char* filename, bool loop ){

  /*
   * Play a sound in loop
   */
  soundDevice->play2D(filename, true);
}