#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "../gui/gui.h"

using namespace std;

enum cardIdInv {
    strike,
    defend
};

class Character : public Gui
{
    public:
        Character(int health_);
        void display_block();
        void display_hp();
        void display_energy();
        void character_display();
        void gain_block(int amount);
        void take_damge(int dmg);
        void update_energy_text();
        void lose_energy(int amount);
        
        static double maxHealth;
        static int health;
        static int energy;
        Text energyText = Text(50, rect.x+10, rect.y+260, 200, 200, 200);
        int block;
        static std::vector<cardIdInv> cardInventoryId;
};

