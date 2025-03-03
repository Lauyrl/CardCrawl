#pragma once

#include <iostream>
#include "../gui/gui.h"
#include "../game.h"

using namespace std;

class EndTurnButton : public Gui 
{
    public:
        EndTurnButton();
        void display();
        Text etText = Text(30, rect.x, rect.y, 100, 100, 100);
};
