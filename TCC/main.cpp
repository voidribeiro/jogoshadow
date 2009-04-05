/** IrrLicht First Time Walk **/

#include "game/GameManager.h"
#include <iostream>

int main()
{
  GameManager* game = new GameManager();
  if( game->init() ){
    game->draw();
  }

	return 0;
}
