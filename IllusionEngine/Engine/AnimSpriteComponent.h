#pragma once
#include "SpriteComponent.h"


class AnimSpriteComponent : public SpriteComponent
{
public :
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimSpriteComponent();

	// ���t���[���X�V
	void Update(float deltaTime) override;
	// �A�j���[�V�����e�N�X�`���z��ݒ�
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// �A�j���[�V����FPS�ݒ�
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	// �A�j���[�V����FPS�擾
	float GetAnimFPS() const { return mAnimFPS; }
	// Component��ގ擾
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Anime2D); }
private:
	// �A�j���[�V�����e�N�X�`���̓��I�z��
	std::vector<SDL_Texture*> mAnimTextures;
	// ���݂̃A�j���[�V�����t���[��
	float mCurrFrame;
	// �A�j���[�V����FPS
	float mAnimFPS;
};