#pragma once
#include "IllusionEngine.h"
#include "GameFile/Game02Space/Ship.h"

#define _WINDOW_HEIGHT 768.0
#define _WINDOW_WIDTH 1024.0
#define _WINDOW_NAME "Game02Space_IllusionEngine"

class Game02Space :public GameMain {


	virtual void EnginePreSetting() override;
	// Game������/�I������
	virtual void Initialize() override;
	virtual void Finalize() override;
	// �t���C�������̒��g
	virtual void ProcessInput() override;
	virtual void Update() override;
	virtual void GenerateOutput() override;

	// �Q�[���I�u�W�F�N�g

	int mPaddleDir;
	int mPaddle2Dir;

	Vector2 mPaddlePos;
	Vector2 mPaddle2Pos;

	Vector2 mBallPos;
	Vector2 mBallVel;


};