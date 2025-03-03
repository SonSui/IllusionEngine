#pragma once
#include "IllusionEngine.h"
#include "BGSpriteComponent.h"
#include "TileMapComponent.h"

#define _WINDOW_HEIGHT 768.0
#define _WINDOW_WIDTH 1024.0
#define _WINDOW_NAME "Game03TileMapTest_IllusionEngine"

class Game03TileMapTest : public GameMain
{


	virtual void EnginePreSetting() override;
	// Game������/�I������
	virtual void Initialize() override;
	virtual void Finalize() override;
	// �t���C�������̒��g
	virtual void ProcessInput() override;
	virtual void Update() override;
	virtual void GenerateOutput() override;

	// �Q�[���I�u�W�F�N�g
	TileMapComponent* mTileMap;
};