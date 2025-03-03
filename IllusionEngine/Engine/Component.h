#pragma once
#include "IllusionEngine.h"

class Component
{
public:
	// コンポーネントの種類
	enum ComponentType : uint64_t {
		None = 0,
		Sprite = 1 << 0,
		Collider2D = 1 << 1,
		Anime2D = 1 << 2,
		TileMap = 1 << 3,
	};
	// コンストラクター
	Component(class Actor* owner, int updateOrder = 100);
	// デストラクター
	virtual ~Component();

	// 更新
	virtual void Update(float deltaTime);
	// 更新順取得
	int GetUpdateOrder() const { return mUpdateOrder; }
	// コンポーネントの種類取得
	virtual uint64_t GetComponentType() {  return static_cast<uint64_t>(ComponentType::None); }
protected:

	// オーナー
	class Actor* mOwner;
	// 更新順
	int mUpdateOrder;
};

