#pragma once
#include "IllusionEngine.h"
#include "IMath.h"

class Actor {
public:
	// Actor�̏��
	enum State {
		EActive,
		EPaused,
		EDead
	};
	Actor(class GameMain* game);
	virtual ~Actor();


	// �Q�[������ĂԖ��t���[���X�V
	void Update(float deltaTime);
	// Component�X�V
	void UpdateComponents(float deltaTime);
	// Actor �X�V
	virtual void UpdateActor(float deltaTime);

	State GetState() { return mState; }

	// Component�ǉ�
	void AddComponent(class Component* component);
	// Component�폜
	void RemoveComponent(class Component* component);



	// �傫���ݒ�
	void SetScale(float scale) { mScale = scale; }
	// �傫���擾
	float GetScale() { return mScale; }
	// �ʒu�ݒ�
	void SetPosition(Vector2 pos) { mPosition = pos; }
	// �ʒu�擾
	Vector2 GetPosition() { return mPosition; }
	// ��]�ݒ�
	void SetRotation(float rot) { mRotation = rot; }
	// ��]�擾
	float GetRotation() { return mRotation; }
	
	// �Q�[���擾
	class GameMain* GetGame() { return mGame; }
private:
	// Actor�̏��
	State mState;
	// �ʒu
	Vector2 mPosition;
	// �傫��
	float mScale;
	// ��]
	float mRotation; 

	// Component
	std::vector<class Component*> mComponents;
	// Component�̎��
	uint64_t mComponentMask;
	// �Q�[��
	class GameMain* mGame;
};