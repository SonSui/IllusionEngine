
#include "GameFile/Game02Space/Game02Space.h"


int main()
{
	// Component�V�X�e���ǉ����邱�ƂŁA�Q�[��01�̃\�[�X�R�[�h��STL�`��𒼐ڂɎg���ƕs����ɂȂ�
	Game02Space game;
	
	bool success = game.EngineInitialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();

	return 0;
}