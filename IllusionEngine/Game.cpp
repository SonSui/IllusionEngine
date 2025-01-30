#include "Game.h"
#include "cmath"
#include "random"
#define TICKS_PASSED(a, b) ((Sint64)((a) - (b)) >= 0)
const int thickness = 15;
const float paddleH = 100.0f;
const float moveSpeed = 300.0f;
Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
{
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mPaddle2Pos.x = 1024.0f - 10.0f;
	mPaddle2Pos.y = 768.0f / 2.0f;

	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
}
bool Game::Initialize()
{
	bool sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (!sdlResult)
	{
		SDL_Log("SDL initialize failed : %s",SDL_GetError());
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
	
	mRenderer = SDL_CreateRenderer(mWindow,NULL);

	if(!mRenderer)
	{
		SDL_Log("SDL Render create failed : %s", SDL_GetError());
		return false;
	}

	mTexture = IMG_LoadTexture(mRenderer, "Background.png");

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mPaddle2Pos.x = 1024.0f - 10.0f;
	mPaddle2Pos.y = 768.0f / 2.0f;

	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;


	return true;
}
void Game:: Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			mIsRunning = false;
			break;
		}
	}
	int numKeys;
	const bool* state = SDL_GetKeyboardState(&numKeys);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	mPaddleDir = 0;
	mPaddle2Dir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
	if (state[SDL_SCANCODE_UP])
	{
		mPaddle2Dir -= 1;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		mPaddle2Dir += 1;
	}



}
void Game::UpdateGame()
{
	while (!TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));//16ms��҂�
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// deltaTime�ő�l����
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// player1�@�ړ�����
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * moveSpeed * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))mPaddlePos.y = (paddleH / 2.0f + thickness);
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))mPaddlePos.y = (768.0f - paddleH / 2.0f - thickness);
	}

	// player2�@�ړ�����
	if (mPaddle2Dir != 0)
	{
		mPaddle2Pos.y += mPaddle2Dir * moveSpeed * deltaTime;
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness))mPaddle2Pos.y = (paddleH / 2.0f + thickness);
		else if (mPaddle2Pos.y > (768.0f - paddleH / 2.0f - thickness))mPaddle2Pos.y = (768.0f - paddleH / 2.0f - thickness);
	}

	// �ʂ̈ړ�
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// �ǂԂ��鏈��                                       
	if ((mBallPos.y <= thickness && mBallVel.y < 0.0f) || (mBallPos.y >= 768 - thickness && mBallVel.y > 0.0f))
	{
		mBallVel.y *= -1;
	}

	if (mBallPos.x < -10.0f || mBallPos.x > 1034.0f)
	{
		mBallPos.x = 1024.0f / 2.0f;
		mBallPos.y = 768.0f / 2.0f;
		std::random_device rd;  
		std::mt19937 gen(rd()); 

		std::uniform_int_distribution<int> dist(150, 300);

		int vx = dist(gen);
		int vy = dist(gen);

		
		if (mBallVel.x > 0)mBallVel.x = -1.0f * vx;
		else mBallVel.x = 1.0f * vx;
		if (mBallVel.y > 0)mBallVel.y = -1.0f * vy;
		else mBallVel.y = -1.0f * vy;
	}



	
	// player1 �Փ˔���
	float diff_player1 = fabs(mPaddlePos.y - mBallPos.y);

	if (diff_player1 <= paddleH / 2.0f &&
		mBallPos.x <= 25.0f && mBallPos.x >= 5.0f &&
		mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.1f;
	}

	// player2�@�Փ˔���
	float diff_player2 = fabs(mPaddle2Pos.y - mBallPos.y);
	if (diff_player2 <= paddleH / 2.0f &&
		mBallPos.x >= 999.0f && mBallPos.x <= 1019.0f &&
		mBallVel.x > 0.0f
		)
	{
		mBallVel.x *= -1.1f;
	}





	
}
void Game::GenerateOutput()
{
	// �w�i�`��
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	SDL_FRect dst = { 0,0,1024,768 };

	SDL_RenderTexture(mRenderer, mTexture, NULL, &dst);
	
	//�@��Ɖ��̕�
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_FRect wall
	{
		0,0,1024,thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//�@��
	SDL_FRect ball{
		static_cast<int>(mBallPos.x - thickness / 2), //���W�𒆐S�ɂ��āAfloat��int�ɕϊ���
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_RenderFillRect(mRenderer, &ball);

	// �v���C���[�P
	SDL_FRect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2), //���W�𒆐S�ɂ��āAfloat��int�ɕϊ���
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		(int)paddleH
	};
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, &paddle);
	//�v���C���[�Q
	SDL_FRect paddle2{
		static_cast<int>(mPaddle2Pos.x - thickness / 2), //���W�𒆐S�ɂ��āAfloat��int�ɕϊ���
		static_cast<int>(mPaddle2Pos.y - paddleH / 2),
		thickness,
		(int)paddleH
	};
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(mRenderer, &paddle2);



	SDL_RenderPresent(mRenderer);

}