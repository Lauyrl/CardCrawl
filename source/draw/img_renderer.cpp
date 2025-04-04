#include "../../incl/libraries.h"
#include "../game.h"

SDL_Texture* Game::load_texture(const char *fileName)
{
	if (textureMap.find(fileName) == textureMap.end())
	{
		SDL_Texture *texture = IMG_LoadTexture(renderer, fileName);
		if (!texture)
			std::cerr << "Failed to load texture. " << IMG_GetError();
		textureMap[fileName] = texture;
		return texture;
	}
	else return  textureMap.at(fileName);
}

void Game::render_img(const char *fileName, int posX, int posY, int width, int height, Uint8 alpha, SDL_Rect* clip) //fix the arg format to make it mroe consistent
{
	SDL_Texture* texture = load_texture(fileName);
    SDL_Rect pos{posX, posY, width, height};
	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_RenderCopy(renderer, texture, clip, &pos);
}
