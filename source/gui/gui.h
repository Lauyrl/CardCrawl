#pragma once

#include <iostream>
#include "../../incl/libraries.h"
#include "../input/cursor_variables.h"
#include "../draw/text.h"

class Gui 
{
    public:
        Gui(int posX, int posY, int width, int height);
        ~Gui();
        SDL_Rect rect;
        bool detect_cursor_hover();
        bool detect_click();
        void move_rect(int newX, int newY);
};


