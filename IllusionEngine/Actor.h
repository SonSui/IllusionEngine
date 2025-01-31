#pragma once
class Actor {
public:
	// Actor 毎フレーム更新
	virtual void Update(float deltaTime);
	// Acoor 毎フレーム描画
	virtual void Draw();
};