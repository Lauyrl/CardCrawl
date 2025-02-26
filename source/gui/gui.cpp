#include "gui.h"

Gui::Gui(int x_root, int y_root, int width, int height)
{
    rect = SDL_Rect{x_root, y_root, width, height};
}

int testCnt{0};
bool Gui::detect_cursor_hover(int cursorX, int cursorY)
{
    if (cursorX > rect.x && cursorX < rect.x+rect.w && cursorY > rect.y && cursorY < rect.y+rect.h) 
    {
        // std::cout << "Detected " << test << std::endl;
        testCnt++;
        return true;
    }
    return false;
}

void Gui::move_rect(int new_x, int new_y)
{
    rect.x = new_x;
    rect.y = new_y;
}

Gui::~Gui()
{

}
