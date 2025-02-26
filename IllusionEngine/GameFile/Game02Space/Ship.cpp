#include "Ship.h"

#define texture1 "Assets/Ship01.png"
#define texture2 "Assets/Ship02.png"
#define texture3 "Assets/Ship03.png"
#define texture4 "Assets/Ship04.png"

Ship::Ship(class GameMain* game) : Actor(game)
{
	mRightSpeed = 0;
	mDownSpeed = 0;
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	/*std::vector<SDL_Texture*>anims = {
		
	}*/

}

void Ship::UpdateActor(float deltaTime)
{

}

void Ship::PrecessKeyboard(const uint8_t* state)
{

}