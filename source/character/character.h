#pragma once

#include <set>
#include <cstring>
#include "../game.h"
#include "../gui/gui.h"
#include "../gui/fx/fx.h"
#include "conditions.h"
using namespace std;

class Character : public Gui
{
    public:
        Character();
        Character(int health_);
        void display_attacked_fx();
        void display_statuses();
        void display_energy();
        void display_block();
        void display_hp();
        void display(bool info = true);
        void heal(int amount);
        void gain_block(int amount);
        void take_damage(int amount, int delay = 0);
        void lose_energy(int amount);
        void add_relic(relicId id);
        
        double maxHealth;
        int health;
        int gold{0};
        int energy{3};
        int block;
        void variables_reset();
        Text blockText  = Text(22, rect.x+65, rect.y+191, 140, 30, 0);
        Text healthText = Text(15, rect.x+155, rect.y+195, 255, 255, 255);
        Text energyText = Text(50, rect.x+85, rect.y+315, 200, 200, 200);

        int attackCardsCnt{0};
        int slimedCnt{0};
        int burnCnt{0};
        int voidCnt{0};
        int flexCnt{0}; //reset in decrement_statuses()
        bool raged{false};

        

        static map<relicId, Relic> relicInv;
        bool check_relic(relicId id);
        bool check_relic_active(relicId id);
        void reformat_relics();
        void combat_start_relic();
        void during_turn_relic();
        void during_turn_relic_renew();

        static map<statusId, Status> statuses;
        void decrement_statuses();
        void cleanse();

        bool hit{false};
        int shakeT{0};
        vector<DmgText> dmgTextV;
        vector<SlashFx> slashfxV; 
        void shake();

        int currentLevel{0};
        void renew_turn();
        void renew();

        vector<bool> powers;
        
};

extern Character ironclad;
