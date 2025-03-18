#pragma once

#include "../gui/gui.h"
#include "id_to_enemy.h"

const int ENEMY_POS_X = 640;
const int ENEMY_POS_Y = 360;
const int NULL_TARGET = -1;

class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemyId id_, int initPos);
        void display();
        void generate_intent();
        bool enemy_action();
        void display_intent();
        void display_hp();
        void take_damage(int damageTaken);

        int pos;
        enemyId id;
        enemyAttributes attributes;
        vector<possibleActions> possibilities;
        function<void(Enemy&)> intended = [](Enemy&){};
        
        const char* intentSprite = ""; //for testing only

        static const map<enemyId, enemyAttributes> eAttriMap;
};
