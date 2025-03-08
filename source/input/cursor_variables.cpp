#include <iostream>
#include "cursor_variables.h"

int cursorX;
int cursorY;

bool clickQueued = false;
bool clickReleased = false;

// bool process_click()
// {
//     if (clickQueued) 
//     {
//         clickQueued = false; 
//         return true;
//     }
//     return false;
// }
