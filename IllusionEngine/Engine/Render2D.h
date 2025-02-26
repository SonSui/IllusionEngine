#pragma once
#include "IllusionEngine.h"
class Render2D 
{
public:
	SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer** render);
	
};