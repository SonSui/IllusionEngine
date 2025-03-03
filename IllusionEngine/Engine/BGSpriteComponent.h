#pragma once
#include "SpriteComponent.h"


class BGSpriteComponent : public SpriteComponent
{
public :
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	~BGSpriteComponent();

	// 毎フレーム更新
	void Update(float deltaTime) override;
	// 描画
	void Draw(SDL_Renderer* renderer) override;
	// 背景テクスチャ配列設定
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	// 画面サイズ設定
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	// スクロール速度設定
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	// スクロール速度取得
	float GetScrollSpeed() const { return mScrollSpeed; }
	// Component種類取得
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Sprite); }
private:
	// 背景テクスチャ構造体
	struct BGTexture 
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	// 背景テクスチャの動的配列
	std::vector<BGTexture> mBGTextures;
	// 画面サイズ
	Vector2 mScreenSize;
	// スクロール速度
	float mScrollSpeed;
};