#include "Game02Space.h"

#define START_POS_X 100.0f
#define SHIP_SCALE 1.0f
#define BACKGROUND_TEXTURE_1 "GameFile/Game02Space/Assets/Farback01.png"
#define BACKGROUND_TEXTURE_2 "GameFile/Game02Space/Assets/Farback02.png"
#define BACKGROUND_SCROLLSPEED -100.0f
#define BACKGROUND_TEXTURE_STAR "GameFile/Game02Space/Assets/Stars.png"


void Game02Space::EnginePreSetting()
{
	SetWindowSize(Vector2(_WINDOW_WIDTH, _WINDOW_HEIGHT));
	SetWindowName(_WINDOW_NAME);
}


void Game02Space::Initialize()
{
	// �v���C���[
	Vector2 size = GetWidowSize();
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(START_POS_X,size.y/2.0f));
	mShip->SetScale(SHIP_SCALE);

	// �w�i
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(size.x/2.0f,size.y/2.0f));
	// �w�iComponent
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(size.x,size.y));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture(BACKGROUND_TEXTURE_1),
		GetTexture(BACKGROUND_TEXTURE_2)
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(BACKGROUND_SCROLLSPEED);
	// �߂��w�i
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(_WINDOW_WIDTH, _WINDOW_HEIGHT));
	bgtexs = {
		GetTexture(BACKGROUND_TEXTURE_STAR),
		GetTexture(BACKGROUND_TEXTURE_STAR)
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(BACKGROUND_SCROLLSPEED * 2);
	
}
void Game02Space::Finalize()
{

}
void Game02Space::ProcessInput()
{
	mShip->PrecessKeyboard(SDL_Input);
}
void Game02Space::Update()
{
	
}
void Game02Space::GenerateOutput()
{
	
}