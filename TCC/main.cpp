/** Shadows of Time - Adventure Game **/

#include "game/GameManager.h"

int main()
{
  GameManager* game = new GameManager();
  if( game->init() ){
    game->run();
  }

	return 0;
}
