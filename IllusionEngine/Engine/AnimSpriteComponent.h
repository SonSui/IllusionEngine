#pragma once
#include "SpriteComponent.h"


class AnimSpriteComponent : public SpriteComponent
{
public :
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimSpriteComponent();

	// 毎フレーム更新
	void Update(float deltaTime) override;
	// アニメーションテクスチャ配列設定
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// アニメーションFPS設定
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	// アニメーションFPS取得
	float GetAnimFPS() const { return mAnimFPS; }
	// Component種類取得
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Anime2D); }
private:
	// アニメーションテクスチャの動的配列
	std::vector<SDL_Texture*> mAnimTextures;
	// 現在のアニメーションフレーム
	float mCurrFrame;
	// アニメーションFPS
	float mAnimFPS;
};