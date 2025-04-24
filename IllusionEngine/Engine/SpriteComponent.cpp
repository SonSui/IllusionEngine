#include "SpriteComponent.h"
#include "IMath.h"


SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder) :  Component(owner)
, mTexture(nullptr)
, mDrawOrder(drawOrder)
, mTexWidth(0)
, mTexHeight(0)
, isSplitTexture(false)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}
void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (!isSplitTexture&&mTexture)
    {
        SDL_FRect dstRect;
        dstRect.w = static_cast<float>(mTexWidth * mOwner->GetScale());
        dstRect.h = static_cast<float>(mTexHeight * mOwner->GetScale());
        dstRect.x = static_cast<float>(mOwner->GetPosition().x - dstRect.w / 2);
        dstRect.y = static_cast<float>(mOwner->GetPosition().y - dstRect.h / 2);

        SDL_FPoint center = { dstRect.w / 2, dstRect.h / 2 };
        SDL_FlipMode flip = SDL_FLIP_NONE;

        if (!SDL_RenderTextureRotated(renderer, mTexture, nullptr, &dstRect, -IMath::ToDegrees(mOwner->GetRotation()), &center, flip))
        {
            SDL_Log("SDL_RenderTextureRotated failed: %s", SDL_GetError());
        }
    }
    else if (isSplitTexture && mTextureSplitter)
    {
        SDL_FRect dstRect;
        dstRect = mTextureSplitter->GetDefaultTileRect();
        SDL_FPoint center = { dstRect.w / 2, dstRect.h / 2 };
        SDL_FlipMode flip = SDL_FLIP_NONE;

        if (!SDL_RenderTextureRotated(renderer, mTextureSplitter->GetSourceTexture(), nullptr, &dstRect, -IMath::ToDegrees(mOwner->GetRotation()), &center, flip))
        {
            SDL_Log("SDL_RenderTextureRotated failed: %s", SDL_GetError());
        }
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_GetTextureSize(texture, &mTexWidth, &mTexHeight);
}
void SpriteComponent::SetTextureSplitter(TextureSplitter* splitter)
{
	mTextureSplitter = splitter;
	isSplitTexture = true;
}

void SpriteComponent::Update(float dealtime)
{

}
