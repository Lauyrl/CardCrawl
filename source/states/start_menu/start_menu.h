#pragma once

#include "../../character/character.h"
#include "../../gui/gui.h"

class StartButton : public Gui
{
    public:
        StartButton();
        void display();
        void process();
        Text startText = Text(90, 400, 400, 255, 255, 255);
};
