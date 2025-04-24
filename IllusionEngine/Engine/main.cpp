//#include "GameFile/Game01Pong/Game01Pong.h"
#include "GameFile/Game02Space/Game02Space.h"
//#include "GameFile/Game03TileMapTest/Game03TileMapTest.h"

int main()
{
	//Game01Pong game;
	Game02Space game;
	//Game03TileMapTest game;
	bool success = game.EngineInitialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();

	return 0;
}