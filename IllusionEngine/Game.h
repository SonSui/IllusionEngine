#pragma once
#include "IllusionEngine.h"

// Game class
class Game
{
public:
	Game();
	// ������
	bool Initialize();
	// �t���C������
	void RunLoop();
	// �~�߂�
	void Shutdown();
private:
	// �t���C�������̒��g
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// �����_������
	bool InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer);


	// �Q�[���̃E�B���h
	SDL_Window* mWindow;
	// �`��
	SDL_Renderer* mRenderer;
	// �摜
	SDL_Texture* mTexture;
	// �J�n����̎���
	Uint32 mTicksCount;
	// �Q�[�����s���̔��f
	bool mIsRunning;


	// �Q�[���I�u�W�F�N�g
	
	int mPaddleDir;
	int mPaddle2Dir;
	
	Vector2 mPaddlePos;
	Vector2 mPaddle2Pos;

	Vector2 mBallPos;
	Vector2 mBallVel;
};
