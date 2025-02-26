
#include "Game01Pong.h"

int main()
{
	Game01Pong game1;
	bool success = game1.EngineInitialize();
	if (success)
	{
		game1.RunLoop();
	}
	game1.Shutdown();

	return 0;
}