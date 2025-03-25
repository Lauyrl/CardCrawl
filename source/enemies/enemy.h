#pragma once

#include "id_to_enemy.h"
#include "../gui/fx/fx.h"

const int ENEMY_POS_X = 640;
const int ENEMY_POS_Y = 360;
const int NULL_TARGET = -1;

class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemyId id_, int initPos);
        void generate_intent();
        bool enemy_action();
        void display_attacked_fx();
        void display_statuses();
        void display_intent();
        void display_hp();
        void display();
        void take_damage(int damageTaken);
        void deal_damage(int dmg);
        void decrement_statuses();

        int pos;
        enemyId id;
        enemyAttributes attributes;
        map<statusId, Status> statuses = globalStatuses;

        Intent intentUI;
        function<void(Enemy&)> intended = [](Enemy&){};
        vector<possibleActions> possibilities;
        Text healthText = Text(0,0,0,0,0,0);

        static const map<enemyId, enemyAttributes> eAttriMap;

        bool hit{false};
        int shakeT{0};
        vector<DmgText> dmgTextV;
        vector<SlashFX> slashfxV; 
        void shake();
};
