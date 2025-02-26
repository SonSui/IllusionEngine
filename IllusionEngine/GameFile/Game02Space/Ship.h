#pragma once
#include "Actor.h"
#include "AnimSpriteComponent.h"
class Ship :public Actor
{
public :
	Ship(class GameMain* game);
	void UpdateActor(float deltaTime) override;
	void PrecessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
	void SetShipSize(Vector2 size) { shipSize = size; }
	Vector2 GetShipSize() { return shipSize; }
private:
	float mRightSpeed;
	float mDownSpeed;

	Vector2 shipSize;
};