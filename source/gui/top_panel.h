#pragma once

#include "../cards/deck.h"

class DeckButton : public Gui
{
    public:
        DeckButton();
        void display();
        void process();
        bool active{false};
};
class TopPanel
{
    public:
        TopPanel();
        void display();
        Text healthText = Text(16, 50, 15, 255, 40, 40);
        Text goldText = Text(16, 180, 15, 250, 200, 0);
        DeckButton dButton;
        bool inMenu{false};
};



extern TopPanel panel;
