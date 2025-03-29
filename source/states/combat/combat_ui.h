#pragma once

#include "../../game.h"
#include "../../gui/gui.h"
#include "../../cards/deck.h"
#include "../../gui/top_panel.h"

using namespace std;

class EndTurnButton : public Gui 
{
    public:
        EndTurnButton();
        void display();
        Text etText = Text(30, rect.x+12, rect.y, 230, 230, 255);
};

class DrawPileButton : public Gui
{
    public:
        DrawPileButton();
        void display();
        static bool displaying;
        void button_process();
        
};

class DiscardPileButton : public Gui
{
    public:
        DiscardPileButton();
        void display();
        static bool displaying;
        void button_process();
};
