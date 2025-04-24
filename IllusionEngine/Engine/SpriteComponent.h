#pragma once
#include "Component.h"
#include "TextureSplitter.h"

class SpriteComponent :public Component
{
public:
	// drawOrder 低いほど遠くに置かれる
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	// 毎フレームエンジンが描画
	virtual void Draw(SDL_Renderer* renderer);
	// テクスチャ設定
	virtual void SetTexture(SDL_Texture* texture);
	// テクスチャ取得
	SDL_Texture* GetTexture() { return mTexture; }
	// 分割テクスチャ設定
	virtual void SetTextureSplitter(TextureSplitter* splitter);
	// 分割テクスチャ取得
	TextureSplitter* GetTextureSplitter() { return mTextureSplitter; }
	// 分割テクスチャ利用しているかどうか
	bool IsSplitTexture() { return isSplitTexture; }
	// 更新
	virtual void Update(float dealtime) override;
	// 描画順設定
	void SetDrawOrder(int order) { mDrawOrder = order; }
	// 描画順取得
	int GetDrawOrder() const { return mDrawOrder; }
	// テクスチャサイズ設定
	void SetTexSize(Vector2 size) { mTexWidth = size.x; mTexHeight = size.y; }
	// テクスチャサイズ取得
	Vector2 GetTexSize() { return Vector2(mTexWidth, mTexHeight); }
	// テクスチャ高さ取得
	float GetTexHeight()const { return mTexHeight; }
	// テクスチャ幅取得
	float GetTexWidth()const { return mTexWidth; }
	// Component種類取得
	virtual uint64_t GetComponentType() { return static_cast<uint64_t>(ComponentType::Sprite); }
protected:
	bool isSplitTexture;
	TextureSplitter* mTextureSplitter; // 分割テクスチャ
	SDL_Texture* mTexture; // 普通のテクスチャ
	int mDrawOrder;
	float mTexWidth;
	float mTexHeight;
};