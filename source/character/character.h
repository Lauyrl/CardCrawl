#pragma once

#include <cstring>
#include "../game.h"
#include "../gui/gui.h"

using namespace std;

enum cardIdInv {
    strike,
    defend,
    iron_wave
};

class Character : public Gui
{
    public:
        Character(int health_);
        void display_block();
        void display_hp();
        void display_energy();
        void display();
        void gain_block(int amount);
        void take_damge(int dmg);
        void lose_energy(int amount);
        void reset_energy();
        
        static double maxHealth;
        static int health;
        static int energy;
        int block;
        Text energyText = Text(50, rect.x+10, rect.y+260, 200, 200, 200);
        static std::vector<cardIdInv> cardIdInventory;
};

