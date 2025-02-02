#pragma once
#include "IllusionEngine.h"
class Component
{
public:
	// �R���X�g���N�^�[
	Component(class Actor* owner, int updateOrder = 100);
	// �f�X�g���N�^�[
	virtual ~Component();

	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};

