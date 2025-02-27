#include "Game01Pong.h"

#define _WINDOW_HEIGHT 768.0
#define _WINDOW_WIDTH 1024.0
#define _BALL_RANDOM_MIN 150
#define _BALL_RANDOM_MAX 300


const int thickness = 15;
const float paddleH = 100.0f;
const float moveSpeed = 300.0f;

void Game01Pong::EnginePreSetting()
{
	SDL_Log("Engine resetted in Game01 Pong");
	std::string name = "Game01Pong_IllusionEngine";
	SetWindowName(name);
}


void Game01Pong::Initialize()
{
	
	mTexture = IMG_LoadTexture(mRenderer, "GameFile/Game01Pong/Assets/Background_Game01.png");

	if (!mTexture)
	{
		SDL_Log("SDL Texture create texture failed : %s", SDL_GetError());
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = _WINDOW_HEIGHT / 2.0f;
	mPaddle2Pos.x = _WINDOW_WIDTH - 10.0f;
	mPaddle2Pos.y = _WINDOW_HEIGHT / 2.0f;

	mBallPos.x = _WINDOW_WIDTH / 2.0f;
	mBallPos.y = _WINDOW_HEIGHT / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

}




void Game01Pong::ProcessInput()
{
	
	mPaddleDir = 0;
	mPaddle2Dir = 0;
	if (SDL_Input[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (SDL_Input[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
	if (SDL_Input[SDL_SCANCODE_UP])
	{
		mPaddle2Dir -= 1;
	}
	if (SDL_Input[SDL_SCANCODE_DOWN])
	{
		mPaddle2Dir += 1;

	}
	


}
void Game01Pong::Update()
{

	

	// player1　移動処理
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * moveSpeed * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))mPaddlePos.y = (paddleH / 2.0f + thickness);
		else if (mPaddlePos.y > (_WINDOW_HEIGHT - paddleH / 2.0f - thickness))mPaddlePos.y = (_WINDOW_HEIGHT - paddleH / 2.0f - thickness);
	}

	// player2　移動処理
	if (mPaddle2Dir != 0)
	{
		mPaddle2Pos.y += mPaddle2Dir * moveSpeed * deltaTime;
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness))mPaddle2Pos.y = (paddleH / 2.0f + thickness);
		else if (mPaddle2Pos.y > (_WINDOW_HEIGHT - paddleH / 2.0f - thickness))mPaddle2Pos.y = (_WINDOW_HEIGHT - paddleH / 2.0f - thickness);
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
		mBallPos.x = _WINDOW_WIDTH / 2.0f;
		mBallPos.y = _WINDOW_HEIGHT / 2.0f;
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dist(_BALL_RANDOM_MIN, _BALL_RANDOM_MAX);

		int vx = dist(gen);
		int vy = dist(gen);


		if (mBallVel.x > 0)mBallVel.x = -1.0f * vx;
		else mBallVel.x = 1.0f * vx;
		if (mBallVel.y > 0)mBallVel.y = -1.0f * vy;
		else mBallVel.y = -1.0f * vy;

		SDL_Log(mBallVel.toString());
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
		SDL_Log("Ball Speed Vector:");
		SDL_Log(mBallVel.toString());
	}

	// player2　衝突判定
	float diff_player2 = fabs(mPaddle2Pos.y - mBallPos.y);
	if (diff_player2 <= paddleH / 2.0f &&
		mBallPos.x >= _WINDOW_WIDTH -25.0f && mBallPos.x <= _WINDOW_WIDTH - 5.0f &&
		mBallVel.x > 0.0f
		)
	{
		mBallVel.x *= -1.1f;
		SDL_Log("Ball Speed Vector:");
		SDL_Log(mBallVel.toString());
	}


}
void Game01Pong::GenerateOutput()
{
	// 背景描画
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	SDL_FRect draw = { 0,0,_WINDOW_WIDTH,_WINDOW_HEIGHT };

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
void Game01Pong::Finalize()
{
	//SDL_DestroyTexture(mTexture);
}