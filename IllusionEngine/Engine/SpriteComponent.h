#pragma once
#include "Component.h"
#include "TextureSplitter.h"

class SpriteComponent :public Component
{
public:
	// drawOrder �Ⴂ�قǉ����ɒu�����
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	// ���t���[���G���W�����`��
	virtual void Draw(SDL_Renderer* renderer);
	// �e�N�X�`���ݒ�
	virtual void SetTexture(SDL_Texture* texture);
	// �e�N�X�`���擾
	SDL_Texture* GetTexture() { return mTexture; }
	// �����e�N�X�`���ݒ�
	virtual void SetTextureSplitter(TextureSplitter* splitter);
	// �����e�N�X�`���擾
	TextureSplitter* GetTextureSplitter() { return mTextureSplitter; }
	// �����e�N�X�`�����p���Ă��邩�ǂ���
	bool IsSplitTexture() { return isSplitTexture; }
	// �X�V
	virtual void Update(float dealtime) override;
	// �`�揇�ݒ�
	void SetDrawOrder(int order) { mDrawOrder = order; }
	// �`�揇�擾
	int GetDrawOrder() const { return mDrawOrder; }
	// �e�N�X�`���T�C�Y�ݒ�
	void SetTexSize(Vector2 size) { mTexWidth = size.x; mTexHeight = size.y; }
	// �e�N�X�`���T�C�Y�擾
	Vector2 GetTexSize() { return Vector2(mTexWidth, mTexHeight); }
	// �e�N�X�`�������擾
	float GetTexHeight()const { return mTexHeight; }
	// �e�N�X�`�����擾
	float GetTexWidth()const { return mTexWidth; }
	// Component��ގ擾
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Sprite); }
protected:
	bool isSplitTexture;
	TextureSplitter* mTextureSplitter; // �����e�N�X�`��
	SDL_Texture* mTexture; // ���ʂ̃e�N�X�`��
	int mDrawOrder;
	float mTexWidth;
	float mTexHeight;
};