
#include "GameFile/Game02Space/Game02Space.h"


int main()
{
	// Componentシステム追加することで、ゲーム01のソースコードでSTL描画を直接に使うと不安定になる
	Game02Space game;
	
	bool success = game.EngineInitialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();

	return 0;
}