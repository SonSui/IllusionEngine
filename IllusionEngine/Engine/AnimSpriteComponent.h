#pragma once
#include "SpriteComponent.h"


class AnimSpriteComponent : public SpriteComponent
{
public :
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimSpriteComponent();
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Anime2D); }
private:
	std::vector<SDL_Texture*> mAnimTextures;
	float mCurrFrame;
	float mAnimFPS;
};