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
        bool enemy_action(Character &chara);
        void display_hp();
        void take_damage(int damageTaken);

        int pos;
        enemyId id;
        enemAttributes attributes;
        vector<possibleActions> possibilities;
};
