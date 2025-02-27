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

	float GetScale() { return mScale; }
	Vector2 GetPosition() { return mPosition; }
	float GetRotation() { return mRotation; }
	void SetPosition(Vector2 pos) { mPosition = pos; }
	void SetScale(float scale) { mScale = scale; }
	void SetRotation(float rot) { mRotation = rot; }
	class GameMain* GetGame() { return mGame; }
private:
	State mState;

	Vector2 mPosition;


	float mScale;
	float mRotation; 

	std::vector<class Component*> mComponents;
	class GameMain* mGame;

};