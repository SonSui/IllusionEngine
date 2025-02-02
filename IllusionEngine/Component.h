#pragma once
#include "IllusionEngine.h"
class Component
{
public:
	// コンストラクター
	Component(class Actor* owner, int updateOrder = 100);
	// デストラクター
	virtual ~Component();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};

