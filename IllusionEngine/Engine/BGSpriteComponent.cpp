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
		// それぞれの画面幅分のオフセットを持つ
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
		//画面から出したら、リセット
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
		// 背景の中心
		SDL_FRect r;
		r.w = mScreenSize.x;
		r.h = mScreenSize.y;
		r.x = mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x;
		r.y = mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y;

		// 背景描画
		SDL_RenderTexture(renderer, bg.mTexture, nullptr, &r);

		
	}
}