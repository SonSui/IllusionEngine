#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
struct Vector2
{
	float x;
	float y;
};

// Game class
class Game
{
public:
	Game();
	// 初期化
	bool Initialize();
	// フレイム処理
	void RunLoop();
	// 止める
	void Shutdown();
private:
	// フレイム処理の中身
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// ゲームのウィンド
	SDL_Window* mWindow;
	// 描画
	SDL_Renderer* mRenderer;
	// 画像
	SDL_Texture* mTexture;
	// 開始からの時間
	Uint32 mTicksCount;
	// ゲーム実行中の判断
	bool mIsRunning;


	// ゲームオブジェクト
	
	int mPaddleDir;
	int mPaddle2Dir;
	
	Vector2 mPaddlePos;
	Vector2 mPaddle2Pos;

	Vector2 mBallPos;
	Vector2 mBallVel;
};
