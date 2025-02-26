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
}