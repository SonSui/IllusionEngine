#include "Ship.h"

#define texture1 "GameFile/Game02Space/Assets/Ship01.png"
#define texture2 "GameFile/Game02Space/Assets/Ship02.png"
#define texture3 "GameFile/Game02Space/Assets/Ship03.png"
#define texture4 "GameFile/Game02Space/Assets/Ship04.png"
#define sizeX 64
#define sizeY 29

Ship::Ship(class GameMain* game) : Actor(game)
{
	mRightSpeed = 0;
	mDownSpeed = 0;
	// アニメーション
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*>anims = {
		game->GetTexture(texture1),
		game->GetTexture(texture2),
		game->GetTexture(texture3),
		game->GetTexture(texture4)
	};
	asc->SetAnimTextures(anims);
	// サイズ
	SetShipSize(Vector2(sizeX, sizeY));
}

void Ship::UpdateActor(float deltaTime)
{
	// 移動
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	
	// 移動制御
	Vector2 wSize = GetGame()->GetWidowSize();

	if (pos.x < shipSize.x / 2) { pos.x = shipSize.x / 2; }
	else if (pos.x > (wSize.x - shipSize.x / 2)) { pos.x = wSize.x - shipSize.x / 2; }
	if (pos.y < shipSize.y / 2) { pos.y = shipSize.y / 2; }
	else if (pos.y > (wSize.y - shipSize.y / 2)) { pos.y = wSize.y - shipSize.y / 2; }
	
	SetPosition(pos);
}

void Ship::PrecessKeyboard(const bool* keyboard_Input)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	if (keyboard_Input[SDL_SCANCODE_W])
	{
		mDownSpeed = -500.0f;
	}
	if (keyboard_Input[SDL_SCANCODE_S])
	{
		mDownSpeed = 500.0f;;
	}
	if (keyboard_Input[SDL_SCANCODE_A])
	{
		mRightSpeed = -500.0f;
	}
	if (keyboard_Input[SDL_SCANCODE_D])
	{
		mRightSpeed = 500.0f;
	}
}