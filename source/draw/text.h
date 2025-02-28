#pragma once

#include "../game.h"

extern Game game;

using namespace std; 

class Text
{
    public:
        Text();
        Text(const char* content, int size, double xMultiplier, double yMultiplier, Uint8 r, Uint8 g, Uint8 b);
        void text_texture_update();
        void text_update(const char* newContent);
        void render_text();

        TTF_Font* font;
        SDL_Texture* textTexture;
        SDL_Color textColor;
        SDL_Rect rect;
        const char* textContent;
        int fontSize;   
        double xMult;
        double yMult;
};
void text_init(Text &textObj, const char* content, int size, int x, int y, double xMultiplier, double yMultipler, Uint8 r, Uint8 g, Uint8 b);
