#include <iostream>
#include "mouse_input.h"
// renamed from cursor_variables
int cursorX;
int cursorY;
bool clickQueued = false;
bool clickReleased = false;

bool process_click()
{
    if (clickQueued) 
    {
        clickQueued = false; 
        return true;
    }
    return false;
}

int scrollDirection;
void scroll_val(int &pos, int lowerBound, int upperBound)
{
    if (scrollDirection != SCROLL_NULL && (scrollDirection == SCROLL_DOWN && pos+20 < upperBound) || (scrollDirection == SCROLL_UP && pos-20 > (0-lowerBound))) 
        pos += 50*scrollDirection;
}
