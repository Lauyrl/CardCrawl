#include "../../incl/libraries.h"
#include "../game.h"

SDL_Texture* Game::load_texture(const char *filename)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (!texture)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
	return texture;
}

void Game::render_texture(SDL_Texture *texture, int des_x, int des_y, int des_w, int des_h, SDL_Rect* clip)
{
	SDL_Rect dest{des_x, des_y, des_w, des_h};
	SDL_RenderCopy(renderer, texture, clip, &dest);
}

void Game::render_img(const char *filename, int des_x, int des_y, int des_w, int des_h, SDL_Rect* clip)
{
	SDL_Texture* texture = load_texture(filename);
	if (!texture)
	{
		std::cerr << "Failed to load texture. " << IMG_GetError();
	}
    render_texture(texture, des_x, des_y, des_w, des_h, clip);
	SDL_DestroyTexture(texture);
}

