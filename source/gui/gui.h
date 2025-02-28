#pragma once

#include <iostream>
#include "../../incl/libraries.h"
#include "input/cursor_variables.h"
#include "../draw/text.h"

class Gui 
{
    public:
        Gui(int x_root, int y_root, int width, int height);
        ~Gui();
        bool detect_cursor_hover(int cx, int cy);
        bool detect_click();
        SDL_Rect rect;
        void move_rect(int new_x, int new_y);
};


