#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "IMath.h"
#include "Component.h"
#include "Actor.h"
#include <vector>
#include <algorithm>
#include <unordered_map>







class SpriteComponent;

class GameMain {

public:
	GameMain();
	// ������
	bool EngineInitialize();
	// �t���C������
	void RunLoop();
	// �S�̏I������
	void Shutdown();


	
	void AddActor(Actor* actor);
	void AddSprite(SpriteComponent* sprite);
	SDL_Texture* GetTexture(const std::string& fileName);

	Vector2 GetWidowSize() { return mWindowSize; }
	void SetWindowSize(Vector2 size) { mWindowSize = size; }
	std::string GetWindowName() { return mWindowName; }
	void SetWindowName(std::string name) { mWindowName = name; };
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
	
	virtual void EnginePreSetting();
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
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// �J�n����̎���
	Uint32 mTicksCount;


	float deltaTime;

	const bool* SDL_Input;


	
	bool mUpdatingActors;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	// �`�揇
	std::vector<SpriteComponent* > mSprites;
	
	Vector2 mWindowSize;
	std::string mWindowName;
	
};
