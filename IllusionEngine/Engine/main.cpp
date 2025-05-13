
#include "GameFile/Game02Space/Game02Space.h"


int main()
{
	
	Game02Space game;
	
	bool success = game.EngineInitialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();

	return 0;
}