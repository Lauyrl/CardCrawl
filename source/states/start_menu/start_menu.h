#pragma once

#include "../../character/character.h"
#include "../../pools/pools.h"
#include "../../gui/gui.h"

class StartButton : public Gui
{
    public:
        StartButton();
        void display();
        void process();
        Text startText = Text(90, 440, 400, 255, 255, 255);
};
