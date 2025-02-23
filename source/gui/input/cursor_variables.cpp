#include "cursor_variables.h"

int cursorX;
int cursorY;

bool clickQueued = false;

bool process_click(bool &detector)
{
    if (detector)
    {
        detector = false;
        return true;
    }
    return false;
}
