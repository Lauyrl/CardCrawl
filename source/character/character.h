#pragma once

#include <vector>
#include <iostream>
#include "../gui/gui.h"

enum cardIdInv {
    strike,
    defend
};

class Character : public Gui
{
    public:
        Character(int health);
        Character init(int health);
        void display_block();
        void display_hp();
        void character_display();
        void gain_block(int amount);
        void take_damge(int dmg);
        
        static double maxHealth;
        static int health;
        static int energy;
        int block;
        static std::vector<cardIdInv> cardInventoryId;
};

