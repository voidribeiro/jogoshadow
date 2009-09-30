/** Shadows of Time - Adventure Game **/

#include "GameManager.h"
#include "ComponentManager.h"

int main(int argc, char* argv[])
{
  GameManager* game = new GameManager(argv[0]);
  if( game->init() ){
    game->run();
  }

	return 0;
}
