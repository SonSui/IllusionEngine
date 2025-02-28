#pragma once
#include "IllusionEngine.h"

class Component
{
public:
	enum ComponentType : uint64_t {
		None = 0,
		Sprite = 1 << 0,
		Collider2D = 1 << 1,
		Anime2D = 1 << 2,
	};
	// コンストラクター
	Component(class Actor* owner, int updateOrder = 100);
	// デストラクター
	virtual ~Component();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
	virtual uint64_t GetComponentType() {  return static_cast<uint64_t>(ComponentType::None); }
protected:
	class Actor* mOwner;
	// 更新順
	int mUpdateOrder;
};

