#pragma once
#include "IllusionEngine.h"
#include "IMath.h"

class Actor {
public:
	// Actorの状態
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
	// Component削除
	void RemoveComponent(class Component* component);



	// 大きさ設定
	void SetScale(float scale) { mScale = scale; }
	// 大きさ取得
	float GetScale() { return mScale; }
	// 位置設定
	void SetPosition(Vector2 pos) { mPosition = pos; }
	// 位置取得
	Vector2 GetPosition() { return mPosition; }
	// 回転設定
	void SetRotation(float rot) { mRotation = rot; }
	// 回転取得
	float GetRotation() { return mRotation; }
	
	// ゲーム取得
	class GameMain* GetGame() { return mGame; }
private:
	// Actorの状態
	State mState;
	// 位置
	Vector2 mPosition;
	// 大きさ
	float mScale;
	// 回転
	float mRotation; 

	// Component
	std::vector<class Component*> mComponents;
	// Componentの種類
	uint64_t mComponentMask;
	// ゲーム
	class GameMain* mGame;
};