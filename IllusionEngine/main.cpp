//#include "Game.h"
#include "Game01Pong.h"

int main()
{
	/*Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();*/
	Game01Pong game1;
	bool success = game1.EngineInitialize();
	if (success)
	{
		game1.RunLoop();
	}
	game1.Shutdown();

	return 0;
}