#pragma once
#include "IllusionEngine.h"

class Component
{
public:
	// �R���|�[�l���g�̎��
	enum ComponentType : uint64_t {
		None = 0,
		Sprite = 1 << 0,
		Collider2D = 1 << 1,
		Anime2D = 1 << 2,
		TileMap = 1 << 3,
	};
	// �R���X�g���N�^�[
	Component(class Actor* owner, int updateOrder = 100);
	// �f�X�g���N�^�[
	virtual ~Component();

	// �X�V
	virtual void Update(float deltaTime);
	// �X�V���擾
	int GetUpdateOrder() const { return mUpdateOrder; }
	// �R���|�[�l���g�̎�ގ擾
	virtual uint64_t GetComponentType() {  return static_cast<uint64_t>(ComponentType::None); }
protected:

	// �I�[�i�[
	class Actor* mOwner;
	// �X�V��
	int mUpdateOrder;
};

