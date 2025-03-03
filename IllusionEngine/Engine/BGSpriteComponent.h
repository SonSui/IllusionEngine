#pragma once
#include "SpriteComponent.h"


class BGSpriteComponent : public SpriteComponent
{
public :
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	~BGSpriteComponent();

	// ���t���[���X�V
	void Update(float deltaTime) override;
	// �`��
	void Draw(SDL_Renderer* renderer) override;
	// �w�i�e�N�X�`���z��ݒ�
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// ��ʃT�C�Y�ݒ�
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	// �X�N���[�����x�ݒ�
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	// �X�N���[�����x�擾
	float GetScrollSpeed() const { return mScrollSpeed; }
	// Component��ގ擾
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Sprite); }
private:
	// �w�i�e�N�X�`���\����
	struct BGTexture 
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	// �w�i�e�N�X�`���̓��I�z��
	std::vector<BGTexture> mBGTextures;
	// ��ʃT�C�Y
	Vector2 mScreenSize;
	// �X�N���[�����x
	float mScrollSpeed;
};