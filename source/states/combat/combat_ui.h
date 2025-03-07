#pragma once

#include "../../gui/gui.h"
#include "../../game.h"

using namespace std;

class EndTurnButton : public Gui 
{
    public:
        EndTurnButton();
        void display();
        Text etText = Text(30, rect.x+10, rect.y, 200, 200, 200);
};

class DrawPileButton : public Gui
{
    public:
        DrawPileButton();
        void display();
};

class DiscardPileButton : public Gui
{
    public:
        DiscardPileButton();
        void display();
};
