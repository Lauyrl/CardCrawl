#pragma once

#include <cmath>
#include "../../game.h"
#include "../../draw/text.h"

class Fx
{
    public:
        Fx(int x_, int y_, int delay = 0);
        int t{0};
        int x, y;
};
class SlashFx : public Fx
{
    public: 
        SlashFx();
        SlashFx(int x_, int y_, int delay = 0);
        bool display();

};

class DmgText : public Fx
{
    public:
        DmgText(int dmg_, int x_, int y_, int delay = 0);
        bool display();
        Text dmgText = Text(0,0,0,0,0,0);
        int dmg{0};
};
