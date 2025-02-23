#include "gui.h"

int test{0};

Gui::Gui(int x_root, int y_root, int width, int height)
{
    x = x_root;
    y = y_root;
    w = width;
    h = height;
    rect = SDL_Rect{x, y, w, h};
}

bool Gui::detect_cursor_hover(int cursorX, int cursorY)
{
    if (cursorX > rect.x && cursorX < rect.x+rect.w && cursorY > rect.y && cursorY < rect.y+rect.h) 
    {
        // std::cout << "Detected " << test << std::endl;
        test++;
        return true;
    }
    return false;
}

void Gui::move_rect(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
    rect.x = x;
    rect.y = y;
}

Gui::~Gui()
{

}
