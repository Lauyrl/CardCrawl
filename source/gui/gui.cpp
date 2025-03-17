#include "gui.h"

Gui::Gui(int posX, int posY, int width, int height) { rect = {posX, posY, width, height}; }


bool Gui::detect_cursor_hover()
{
    static int testCnt{0};
    if (cursorX > rect.x && cursorX < rect.x+rect.w && cursorY > rect.y && cursorY < rect.y+rect.h) 
    {
        // std::cout << "Detected " << testCnt << std::endl;
        // testCnt++;
        return true;
    }
    return false;
}

bool Gui::detect_click()
{
    if (detect_cursor_hover()) return process_click();
    return false;
}

void Gui::move_rect(int newX, int newY)
{
    rect.x = newX;
    rect.y = newY;
}
