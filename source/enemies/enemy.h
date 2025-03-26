#pragma once

#include "action_generation.h"
#include "../gui/fx/fx.h"

const int ENEMY_POS_X = 640;
const int ENEMY_POS_Y = 360;
const int NULL_TARGET = -1;

class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemyId id_, int pos_, int x);
        void generate_intent(int turn);
        bool enemy_action();
        void display_attacked_fx();
        void display_statuses();
        void display_intent();
        void display_block();
        void display_hp();
        void display();
        void heal(int amount);
        void gain_block(int amount);
        void take_damage(int amount);
        void deal_damage(int dmg);
        void decrement_statuses();

        int phase{0};

        int pos;
        int size;
        int block{0};
        double maxHealth;
        enemyId id;
        enemyAttributes attributes;
        map<statusId, Status> statuses = globalStatuses;

        Intent intentUI = Intent(buff1);
        function<void(Enemy&)> intended = [](Enemy&){};
        vector<possibleActions> possibilities;
        Text healthText = Text(0,0,0,0,0,0);
        Text blockText  = Text(0,0,0,0,0,0);

        static const map<enemyId, enemyAttributes> eAttriMap;

        bool hit{false};
        int shakeT{0};
        vector<DmgText> dmgTextV;
        vector<SlashFX> slashfxV; 
        void shake();
};
