#include "text.h"

Text::Text(int fontSize_, int posX, int posY, Uint8 r, Uint8 g, Uint8 b) 
{
    fontSize = fontSize_;
    tRect  = {posX, posY, 1, 1};
    tColor = {r, g, b, 255};//the 'g' value of tColor is used as a key to 
                            //textTextureMap so make microchanges if overlap 
}

SDL_Texture* Text::load_text_texture(string textContent, TTF_Font* font)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, textContent.c_str(), tColor, 1200);
    SDL_Texture* textTexture = NULL;
    if (game.textTextureMap.find(textContent+to_string(tColor.g)) == game.textTextureMap.end())
    {
        textTexture = SDL_CreateTextureFromSurface(game.renderer, textSurface);
        game.textTextureMap[textContent+to_string(tColor.g)] = textTexture;
    }
    else textTexture = game.textTextureMap.at(textContent+to_string(tColor.g));
    SDL_FreeSurface(textSurface);
    SDL_QueryTexture(textTexture, NULL, NULL, &tRect.w, &tRect.h);
    return textTexture;
}

void Text::render_text(string textContent)
{
    TTF_Font* font = NULL;
    if (game.fontMap.find(fontSize) == game.fontMap.end())
    {
        font = TTF_OpenFont("assets/Kreon-Regular.ttf", fontSize);
        game.fontMap[fontSize] = font;
    }
    else font = game.fontMap.at(fontSize);
    SDL_Texture* textTexture = load_text_texture(textContent, font);
    SDL_RenderCopy(game.renderer, textTexture, NULL, &tRect);
}
