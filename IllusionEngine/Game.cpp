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
		"Illusion Engine", // タイトル
		1024,	// 幅
		768,	// 高さ
		0		// フラグ
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

	mTexture = IMG_LoadTexture(mRenderer, "Background.png");

	if (!mTexture)
	{
		SDL_Log("SDL Texture create texture failed : %s", SDL_GetError());
	}

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
	SDL_DestroyTexture(mTexture);
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
	
	while (!TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));//16msを待つ
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// deltaTime最大値制限
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// player1　移動処理
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * moveSpeed * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))mPaddlePos.y = (paddleH / 2.0f + thickness);
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))mPaddlePos.y = (768.0f - paddleH / 2.0f - thickness);
	}

	// player2　移動処理
	if (mPaddle2Dir != 0)
	{
		mPaddle2Pos.y += mPaddle2Dir * moveSpeed * deltaTime;
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness))mPaddle2Pos.y = (paddleH / 2.0f + thickness);
		else if (mPaddle2Pos.y > (768.0f - paddleH / 2.0f - thickness))mPaddle2Pos.y = (768.0f - paddleH / 2.0f - thickness);
	}

	// 玉の移動
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// 壁ぶつかる処理                                       
	if ((mBallPos.y <= thickness && mBallVel.y < 0.0f) || (mBallPos.y >= 768 - thickness && mBallVel.y > 0.0f))
	{
		mBallVel.y *= -1;
	}

	// 画面から消えたら、逆方向にランダム速度で再発射
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

	// 玉が徐々に速くなる

	// player1 衝突判定
	float diff_player1 = fabs(mPaddlePos.y - mBallPos.y);

	if (diff_player1 <= paddleH / 2.0f &&
		mBallPos.x <= 25.0f && mBallPos.x >= 5.0f &&
		mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.1f;
	}

	// player2　衝突判定
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
	// 背景描画
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	SDL_FRect draw = { 0,0,1024,768 };

	SDL_RenderTexture(mRenderer, mTexture, NULL, &draw);
	
	//　上と下の壁
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_FRect wall
	{
		0,0,1024,thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//　玉
	SDL_FRect ball{
		static_cast<int>(mBallPos.x - thickness / 2), //座標を中心にして、floatをintに変換し
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	SDL_RenderFillRect(mRenderer, &ball);

	// プレイヤー１
	SDL_FRect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2), //座標を中心にして、floatをintに変換し
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		(int)paddleH
	};
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, &paddle);
	//プレイヤー２
	SDL_FRect paddle2{
		static_cast<int>(mPaddle2Pos.x - thickness / 2), //座標を中心にして、floatをintに変換し
		static_cast<int>(mPaddle2Pos.y - paddleH / 2),
		thickness,
		(int)paddleH
	};
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(mRenderer, &paddle2);



	SDL_RenderPresent(mRenderer);

}
bool Game::InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer)
{
	int numDrivers = SDL_GetNumRenderDrivers();
	SDL_Log("Number of Render Drivers: %d\n", numDrivers);

	bool opengl_available = false;

	// 全てのレンダを探す
	for (int i = 0; i < numDrivers; ++i) {
		const char* driverName = SDL_GetRenderDriver(i);
		if (driverName) {
			SDL_Log("Driver[%d]: %s", i, driverName);
			if (strcmp(driverName, "opengl") == 0) {
				opengl_available = true;  // OpenGLを使用予定
			}
		}
		else {
			SDL_Log("Error: Cannot get driver name [%d]: %s", i, SDL_GetError());
		}
	}

	if (opengl_available) {
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); // OpenGLを優先的に使用
		*_mRenderer = SDL_CreateRenderer(_mWindow, "opengl");
		SDL_Log("Using OpenGL as the render driver.");
	}
	else {
		*_mRenderer = SDL_CreateRenderer(_mWindow, NULL);
		SDL_Log("Using SDL3 default render driver.");
	}

	if (!*_mRenderer) {
		SDL_Log("SDL Renderer create failed: %s", SDL_GetError());
		return false;
	}

	const char* selected_driver = SDL_GetRenderDriver(0);
	if (selected_driver) {
		SDL_Log("Selected Render Driver: %s", selected_driver);
	}

	return true;
}

