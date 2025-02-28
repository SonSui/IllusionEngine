#pragma once
#include "Component.h"

class SpriteComponent :public Component
{
public:
	// drawOrder ’á‚¢‚Ù‚Ç‰“‚­‚É’u‚©‚ê‚é
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	virtual void Update(float dealtime) override;
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Sprite); }
	int GetDrawOrder() const { return mDrawOrder; }
	float GetTexHeight()const { return mTexHeight; }
	float GetTexWidth()const { return mTexWidth; }
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	float mTexWidth;
	float mTexHeight;
};