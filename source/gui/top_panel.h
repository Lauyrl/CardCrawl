#pragma once

#include "../cards/deck.h"

class TopPanel
{
    public:
        TopPanel();
        void display();
        Text healthText = Text(16, 50, 15, 255, 40, 40);
        Text goldText = Text(16, 180, 15, 250, 200, 0);
};

class DeckButton : public Gui
{
    public:
        DeckButton();
        void display();
        void process();
};


extern TopPanel panel;
