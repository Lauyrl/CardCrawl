#include "../../incl/libraries.h"
#include "../game.h"

SDL_Texture* Game::load_texture(const char *filename)
{
	auto it = textureMap.find(filename);
	if (it == textureMap.end())
	{
		SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
		if (!texture)
			std::cerr << "Failed to load texture. " << IMG_GetError();
		textureMap[filename] = texture;
		return texture;
	}
	else return it->second;
}

void Game::render_img(const char *filename, int des_x, int des_y, int des_w, int des_h, SDL_Rect* clip) //fix the arg format to make it mroe consistent
{
	SDL_Texture* texture = load_texture(filename);
    SDL_Rect dest{des_x, des_y, des_w, des_h};
	SDL_RenderCopy(renderer, texture, clip, &dest);
}
