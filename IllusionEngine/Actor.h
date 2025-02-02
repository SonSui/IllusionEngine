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


	// ゲームから呼ぶ毎フレーム更新
	void Update(float deltaTime);
	// Component更新
	void UpdateComponents(float deltaTime);
	// Actor 更新
	virtual void UpdateActor(float deltaTime);

	State GetState() { return mState; }

	// Component追加
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