#pragma once

#include "../../game.h"
#include "../../pools/pools.h"
#include "../combat/rewards.h"

class Chest : public Gui
{
    public:
        Chest();
        void generate();
        void display();
        void process();
        bool opened;
        int seed;
        const char* sprite;
};
