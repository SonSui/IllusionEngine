#include "SpriteComponent.h"
#include "IMath.h"


SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder) : Component(owner)
{
	mDrawOrder = drawOrder;
}
SpriteComponent::~SpriteComponent()
{

}
void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_FRect r;

		r.w = static_cast<float>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<float>(mTexHeight * mOwner->GetScale());

		r.x = static_cast<float>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<float>(mOwner->GetPosition().y - r.h / 2);

		/*SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&r,
			0,
			nullptr,
			SDL_FLIP_NONE
		);*/

		
		SDL_FPoint center = { r.w / 2, r.h / 2 };  // 回転中心（例として矩形の中心）
		SDL_FlipMode flip = SDL_FLIP_NONE; // フリップモード（必要に応じて設定）

		if (!SDL_RenderTextureRotated(renderer, mTexture, nullptr, &r, -IMath::ToDegrees(mOwner->GetRotation()), &center, flip)) {
			SDL_Log("SDL_RenderTextureRotated failed: %s", SDL_GetError());
		}
		
	}
}
void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_GetTextureSize(texture, &mTexWidth, &mTexHeight);
}
void SpriteComponent::Update(float dealtime)
{

}
