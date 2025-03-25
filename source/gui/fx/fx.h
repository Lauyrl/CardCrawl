#pragma once

#include <cmath>
#include "../../game.h"
#include "../../draw/text.h"

class SlashFX
{
    public: 
        SlashFX();
        SlashFX(int x_, int y_);
        bool display();
        int t{0};
        int x, y;
};

class DmgText
{
    public:
        DmgText(int dmg_, int x_, int y_);
        bool display();
        Text dmgText = Text(0,0,0,0,0,0);
        int t{0};
        int dmg{0};
        int x, y;
};
