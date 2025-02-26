#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner,drawOrder)
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
}