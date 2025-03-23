#pragma once

#include "../gui/gui.h"
#include "id_to_enemy.h"

const int ENEMY_POS_X = 640;
const int ENEMY_POS_Y = 360;
const int NULL_TARGET = -1;
class SlashFX
{
    public: 
        SlashFx();
        void display(int t, int x, int y);
};
class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemyId id_, int initPos);
        void display();
        void generate_intent();
        bool enemy_action();
        void display_statuses();
        void display_intent();
        void display_hp();
        void take_damage(int damageTaken);
        void take_damage_fx();
        void deal_damage(int dmg);

        int pos;
        enemyId id;
        enemyAttributes attributes;
        map<statusId, status> statuses = globalStatuses;
        function<void(Enemy&)> intended = [](Enemy&){};
        vector<possibleActions> possibilities;
        Text healthText = Text(0,0,0,0,0,0);
        const char* intentSprite = ""; //for testing only

        static const map<enemyId, enemyAttributes> eAttriMap;
        bool attacked{false};
        SlashFX slashfx;
        int slashfxT{0};
};
