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