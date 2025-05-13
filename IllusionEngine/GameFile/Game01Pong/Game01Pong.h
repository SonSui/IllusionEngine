#pragma once
#include "IllusionEngine.h"

// Componentシステム追加することで、ゲームのソースコードでSTL描画を直接に使うと不安定になる
class Game01Pong :public GameMain {
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