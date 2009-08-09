#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

/*

Name: SoundManager.h

Description:
  This class is responsible for all music and sound in the game.

*/


#include <stdio.h>
#include <conio.h>

#include "irrKlang.h"

using namespace irrklang;

class SoundManager{
private:
  /*
   * Main Sound Device
   */
  ISoundEngine* soundDevice;

public:
  SoundManager();
  ~SoundManager();

  /*
   * Initializtion
   */
  bool init();

  /*
   * Plays a 2D sound
   */
  void playSound( char* filename, bool loop );

};

#endif