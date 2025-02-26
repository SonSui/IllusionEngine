#include "IllusionEngine.h"
#include "SpriteComponent.h"


#define TICKS_PASSED(a, b) ((Sint64)((a) - (b)) >= 0)

GameMain::GameMain()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mTexture(nullptr)
{
	
}
bool GameMain::EngineInitialize()
{
	// Game�ɂ��ݒ�
	EnginePreSetting();

	// ������
	bool sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (!sdlResult)
	{
		SDL_Log("SDL initialize failed : %s", SDL_GetError());
		return false;
	}

	// �E�B���h�E�Y������
	std::string title = mWindowName;
	Vector2 size = mWindowSize;

	if (size.normalized() == 0)
	{
		// �f�t�H���g�T�C�Y
		mWindowSize.x = 1024;
		mWindowSize.y = 768;
	}
	if (title.empty())
	{
		// �f�t�H���g�^�C�g��
		title = "Illusion Engine";
	}
	mWindow = SDL_CreateWindow(
		title.c_str(), // �^�C�g��
		(int)mWindowSize.x,	// ��
		(int)mWindowSize.y,	// ����
		0		// �t���O
	);
	if (!mWindow)
	{
		SDL_Log("SDL Window create failed : %s", SDL_GetError());
		return false;
	}

	// �`��Render������
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
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyTexture(mTexture);
	SDL_Quit();
}

void GameMain::RunLoop()
{
	while (mIsRunning)
	{
		EngineInput();
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}

}
void GameMain::EngineInput()
{
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT: // �E��́~���N���b�N������A�I��
			mIsRunning = false;
			break;
		}
	}
	int numKeys;
	SDL_Input = SDL_GetKeyboardState(&numKeys);
	if (SDL_Input[SDL_SCANCODE_ESCAPE]) // ESC�ŏI��
	{
		mIsRunning = false;
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
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors) 
	{
		//�����Actor�X�V�����O�ɑ҂��A����̍X�V�ɐV����Actor��ǉ�
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors)
	{
		delete actor;
	}

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

void GameMain::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}
void GameMain::RemoveActor(Actor* actor)
{
	// 
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())//�҂��z��̏ꍇ
	{
		// �Ō�̃G�������g�ƌ������āA�폜
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())//���ʂ̏ꍇ
	{
		// �Ō�̃G�������g�ƌ������āA�폜
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void GameMain::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	// �`��X�V���ʂɍ��킹�đ}��
	for (; iter != mSprites.end(); iter++)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

SDL_Texture* GameMain::GetTexture(const std::string& fileName)
{
	SDL_Texture* text = nullptr;
	
	auto iter = mTextures.find(fileName);

	if (iter != mTextures.end()) // ���ɑ��݂��Ă���̃e�N�X�`���[�͓ǂݍ��܂Ȃ�
	{
		text = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName);
			return nullptr;
		}
		else
		{
			SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
			SDL_DestroySurface(surf);
			if (!text)
			{
				SDL_Log("Failed to convert to texture for %s", fileName);
				return nullptr;
			}
		}
	}
	return text;
}





void GameMain::EnginePreSetting() {}

void GameMain::Initialize(){}
void GameMain::ProcessInput(){}
void GameMain::Update(){}
void GameMain::GenerateOutput(){}
void GameMain::Finalize(){}

