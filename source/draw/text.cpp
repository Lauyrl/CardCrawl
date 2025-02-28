#include "text.h"

Text::Text() {}

Text::Text(const char* content, int size, double xMultiplier, double yMultiplier, Uint8 r, Uint8 g, Uint8 b)
{
	textContent = content;
	fontSize = size;
	xMult = xMultiplier;
	yMult = yMultiplier;
	textColor = {r, g, b, 255};
}

void text_init(Text &textObj, const char* content, int size, int x, int y, double xMultiplier, double yMultiplier, Uint8 r, Uint8 g, Uint8 b)
{
	textObj.textContent = content;
    textObj.fontSize = size;
    textObj.xMult = xMultiplier;
    textObj.yMult = yMultiplier;
    textObj.textColor = {r, g, b, 255};
	textObj.text_texture_update();
	int textureW, textureH;
	SDL_QueryTexture(textObj.textTexture, NULL, NULL, &textureW, &textureH);
	textObj.rect = {x, y, textureW*xMultiplier, textureH*yMultiplier};
}

void Text::text_update(const char* newContent)
{
	text_texture_update();
	int textureW, textureH;
	SDL_QueryTexture(textTexture, NULL, NULL, &textureW, &textureH);
	rect.w = textureW*xMult;
	rect.h = textureH*yMult;
}

void Text::text_texture_update()
{
	if (textTexture)
	{
		SDL_DestroyTexture(textTexture);
		textTexture = NULL;
	}
	font = TTF_OpenFont("assets/Kreon-Regular.ttf", fontSize);
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, textContent, textColor);
	if (!textSurface) cout << "Failed to render text surface. " << TTF_GetError() << endl;
	else 
	{
		textTexture = SDL_CreateTextureFromSurface(game.renderer, textSurface);
        if (!textTexture) cout << "Failed to create text texture. " << TTF_GetError();
		SDL_FreeSurface(textSurface);
	}
}

void Text::render_text()
{
	SDL_RenderCopy(game.renderer, textTexture, NULL, &rect);
	if (!game.isRunning) 
	{
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(font);
	}
}
