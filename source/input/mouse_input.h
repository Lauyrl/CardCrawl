#pragma once

extern int cursorX;
extern int cursorY;
extern bool clickQueued;
extern bool clickReleased;
extern bool process_click();

const int SCROLL_UP  = -1;
const int SCROLL_NULL = 0;
const int SCROLL_DOWN = 1;
extern int scrollDirection;
extern void scroll_val(int &pos, int lowerBound, int upperBound);
