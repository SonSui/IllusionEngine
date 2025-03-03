#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3/SDL_joystick.h"
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


	// Actor�ǉ�
	void AddActor(Actor* actor);
	// Actor�폜
	void RemoveActor(Actor* actor);
	// Sprite�ǉ�
	void AddSprite(SpriteComponent* sprite);
	// Sprite�폜
	void RemoveSprite(SpriteComponent* sprite);
	// �e�N�X�`���擾
	SDL_Texture* GetTexture(const std::string& fileName);

	// �E�B���h�E�T�C�Y�擾
	Vector2 GetWidowSize() { return mWindowSize; }
	// �E�B���h�E�T�C�Y�ݒ�
	void SetWindowSize(Vector2 size) { mWindowSize = size; }
	// �E�B���h�E���擾
	std::string GetWindowName() { return mWindowName; }
	// �E�B���h�E���ݒ�
	void SetWindowName(std::string name) { mWindowName = name; };
	
private:
	// �����_������
	bool InitializeRenderer(SDL_Window* _mWindow, SDL_Renderer** _mRenderer);
	// �t���[���X�V
	void UpdateGame();
	// ����
	void EngineInput();
	// �`��
	void EngineRender();
	// ���s���m�F
	bool mIsRunning;
protected:
	
	// �N���O�̐ݒ�
	virtual void EnginePreSetting();
	// Game������/�I������
	virtual void Initialize();
	virtual void Finalize();
	// �t���C�������̒��g
	virtual void ProcessInput();
	virtual void Update();
	virtual void GenerateOutput();

	

	
	// �N���ݒ�
	Vector2 mWindowSize;
	std::string mWindowName;
	// �Q�[���̃E�B���h
	SDL_Window* mWindow;
	// �`��
	SDL_Renderer* mRenderer;
	// �摜
	SDL_Texture* mTexture;
	// �摜�z��
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// �J�n����̎���
	Uint32 mTicksCount;
	// �O�̃t���[������̎���
	float deltaTime;

	// �L�[�{�[�h���͔z��
	const bool* SDL_Input;


	// Actor�Ǘ�
	bool mUpdatingActors;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	// �`�揇
	std::vector<SpriteComponent* > mSprites;
	

};
