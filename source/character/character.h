#pragma once

#include <set>
#include <cstring>
#include "../game.h"
#include "../gui/gui.h"
#include "relics.h"

using namespace std;

enum cardIdInv {
    strike,
    defend,
    iron_wave
};

class Character : public Gui
{
    public:
        Character();
        Character(int health_);
        void display_block();
        void display_hp();
        void display_energy();
        void display();
        void heal(int amount);
        void gain_block(int amount);
        void take_damge(int dmg);
        void lose_energy(int amount);
        void reset_energy();
        
        static double maxHealth;
        static int health;
        static int gold;
        int energy{3};
        int block;
        static std::vector<cardIdInv> cardIdInv;
        Text energyText = Text(50, rect.x+10, rect.y+260, 200, 200, 200);

        static vector<Relic> relicInv;
        void reformat_relics();
        void combat_start_relic();
        void combat_start_relic_renew();
};

extern Character ironclad;
