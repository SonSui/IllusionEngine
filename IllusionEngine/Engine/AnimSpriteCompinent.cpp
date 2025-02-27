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
		// deltaTimeを基づいて更新
		mCurrFrame += mAnimFPS * deltaTime;

		while (mCurrFrame >= mAnimTextures.size())
		{
			// 巻き戻す
			mCurrFrame -= mAnimTextures.size();
		}
		// 現在のテクスチャを設定
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