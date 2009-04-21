#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include <stdio.h>
#include <conio.h>

#include "../irrKlang/irrKlang.h"

using namespace irrklang;

class SoundManager{
private:
  ISoundEngine* soundDevice;

public:
  SoundManager();
  ~SoundManager();

  bool init();
  void playSound( char* filename, bool loop );

};

#endif