#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int drawOrder) : 
	SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{

}
AnimSpriteComponent::~AnimSpriteComponent()
{

}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// deltaTime����Â��čX�V
		mCurrFrame += mAnimFPS * deltaTime;

		while (mCurrFrame >= mAnimTextures.size())
		{
			// �����߂�
			mCurrFrame -= mAnimTextures.size();
		}
		// ���݂̃e�N�X�`����ݒ�
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if(mAnimTextures.size() > 0)
	{
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}