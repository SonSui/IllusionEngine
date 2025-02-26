#pragma once
#include "IllusionEngine.h"
class Game01Pong :public GameMain {

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