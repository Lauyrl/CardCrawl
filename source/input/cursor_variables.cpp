#include "cursor_variables.h"

int cursorX;
int cursorY;

bool clickQueued = false;

bool process_click(bool &clickQueued)
{
    if (clickQueued) {clickQueued = false; return true;}
    return false;
}
