#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "input/cursor_variables.h"

class Gui 
{
    public:
        Gui(int x_root, int y_root, int width, int height);
        ~Gui();
        bool detect_cursor_hover(int cx, int cy);
        
        int x;
        int y;
        int w;
        int h;
        SDL_Rect rect;
        void move_rect(int new_x, int new_y);
};


