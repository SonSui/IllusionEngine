#include "Render2D.h"

SDL_Texture* Render2D::LoadTexture(const char* fileName,SDL_Renderer** render)
{
	//
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", fileName);
		return nullptr;
	}

	SDL_Texture* text = SDL_CreateTextureFromSurface(*render, surf);

	if (!text)
	{
		SDL_Log("Failed to convert to texture for %s", fileName);
		return nullptr;
	}
	return text;
}