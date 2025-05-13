#pragma once
#include "IllusionEngine.h"

// Component�V�X�e���ǉ����邱�ƂŁA�Q�[���̃\�[�X�R�[�h��STL�`��𒼐ڂɎg���ƕs����ɂȂ�
class Game01Pong :public GameMain {
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