#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{

}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		// ���ꂼ��̉�ʕ����̃I�t�Z�b�g������
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
		
	}
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		bg.mOffset.x += mScrollSpeed * deltaTime; 
		//��ʂ���o������A���Z�b�g
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : mBGTextures)
	{
		// �w�i�̒��S
		SDL_FRect r;
		r.w = mScreenSize.x;
		r.h = mScreenSize.y;
		r.x = mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x;
		r.y = mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y;

		// �w�i�`��
		SDL_RenderTexture(renderer, bg.mTexture, nullptr, &r);

		
	}
}