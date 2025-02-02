#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "IMath.h"
#include "Component.h"
#include "Actor.h"

class GameMain {

public:
	GameMain();
	// ������
	bool EngineInitialize();
	// �t���C������
	void RunLoop();
	// �S�̏I������
	void Shutdown();
private:
	// �����_������
	bool InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer);
	// �t���[���X�V
	void UpdateGame();
	// ����
	void EngineInput();
	// ���s���m�F
	bool mIsRunning;
protected:
	// Game������/�I������
	virtual void Initialize();
	virtual void Finalize();
	// �t���C�������̒��g
	virtual void ProcessInput();
	virtual void Update();
	virtual void GenerateOutput();

	// �Q�[���̃E�B���h
	SDL_Window* mWindow;
	// �`��
	SDL_Renderer* mRenderer;
	// �摜
	SDL_Texture* mTexture;
	// �J�n����̎���
	Uint32 mTicksCount;
	

	float deltaTime;

	const bool* SDL_Input;


	void AddActor(Actor* actor);
	bool mUpdatingActors;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
};
