#include "IllusionEngine.h"
GameMain::GameMain()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
{

}
bool GameMain::EngineInitialize()
{
	bool sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (!sdlResult)
	{
		SDL_Log("SDL initialize failed : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Illusion Engine", // �^�C�g��
		1024,	// ��
		768,	// ����
		0		// �t���O
	);

	if (!mWindow)
	{
		SDL_Log("SDL Window create failed : %s", SDL_GetError());
		return false;
	}


	if (InitializeRenderer(mWindow, &mRenderer) == false)
	{
		return false;
	}
	Initialize();

	return true;
}


void GameMain::Shutdown()
{
	Finalize();
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyTexture(mTexture);
	SDL_Quit();
}

void GameMain::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}
void GameMain::UpdateGame()
{
	while (!TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));//16ms��҂�
	deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// deltaTime�ő�l����
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();
	Update();
}


bool GameMain::InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer)
{
	int numDrivers = SDL_GetNumRenderDrivers();
	SDL_Log("Number of Render Drivers: %d\n", numDrivers);

	bool opengl_available = false;

	// �S�Ẵ����_��T��
	for (int i = 0; i < numDrivers; ++i) {
		const char* driverName = SDL_GetRenderDriver(i);
		if (driverName) {
			SDL_Log("Driver[%d]: %s", i, driverName);
			if (strcmp(driverName, "opengl") == 0) {
				opengl_available = true;  // OpenGL���g�p�\��
			}
		}
		else {
			SDL_Log("Error: Cannot get driver name [%d]: %s", i, SDL_GetError());
		}
	}

	if (opengl_available) {
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); // OpenGL��D��I�Ɏg�p
		*_mRenderer = SDL_CreateRenderer(_mWindow, "opengl");


		if (!*_mRenderer) {
			SDL_Log("OpenGL renderer create failed: %s", SDL_GetError());
		}

	}
	else {
		*_mRenderer = SDL_CreateRenderer(_mWindow, NULL);
		SDL_Log("Using SDL3 default render driver.");
	}

	if (!*_mRenderer) {
		SDL_Log("SDL Default Renderer create failed: %s", SDL_GetError());
		return false;
	}
	const char* info = SDL_GetRendererName(*_mRenderer);
	if (info != NULL)
	{
		SDL_Log("Selected Render Driver: %s", info);
	}

	return true;
}

void GameMain::Initialize()
{

}
void GameMain::ProcessInput()
{

}
void GameMain::Update()
{

}
void GameMain::GenerateOutput()
{

}
void GameMain::Finalize()
{

}