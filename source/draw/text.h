#pragma once

#include "../game.h" //has <string>

using namespace std;

class Text
{
    public:
        //dynamic fonts
        //dynamic textures, temp surfaces
        Text(int fontSize_, int posX, int posY, Uint8 r, Uint8 g, Uint8 b);
        SDL_Texture* load_text_texture(string textContent, TTF_Font* font);
        void render_text(string textContent);
        
        int fontSize;
        SDL_Rect tRect;
        SDL_Color tColor;
};

