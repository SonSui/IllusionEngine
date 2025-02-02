#pragma once
#include "IllusionEngine.h"
#include "IMath.h"

class Actor {
public:
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
	void RemoveComponent(class Component* component);
private:
	State mState;

	Vector2 mPosition;


	float mScale;
	float mRotation;

	std::vector<class Component*> mComponents;
	class GameMain* mGame;

};