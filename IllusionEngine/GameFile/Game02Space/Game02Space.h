#pragma once
#include "IllusionEngine.h"
#include "GameFile/Game02Space/Ship.h"

#define _WINDOW_HEIGHT 768.0
#define _WINDOW_WIDTH 1024.0
#define _WINDOW_NAME "Game02Space_IllusionEngine"

class Game02Space :public GameMain {


	virtual void EnginePreSetting() override;
	// Game初期化/終了処理
	virtual void Initialize() override;
	virtual void Finalize() override;
	// フレイム処理の中身
	virtual void ProcessInput() override;
	virtual void Update() override;
	virtual void GenerateOutput() override;

	// ゲームオブジェクト

	int mPaddleDir;
	int mPaddle2Dir;

	Vector2 mPaddlePos;
	Vector2 mPaddle2Pos;

	Vector2 mBallPos;
	Vector2 mBallVel;


};