#pragma once

#include "../character/character.h"

class TopPanel
{
    public:
        TopPanel();
        void display();
        Character chara;
};

extern TopPanel panel;
