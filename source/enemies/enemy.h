#pragma once

#include "id_to_enemy.h"
#include "../gui/gui.h"

const int NULL_TARGET = -1;

class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemId id_, int initPos);
        void enemy_display();
        void display_hp();
        void take_damage(int damgeTaken);
        void eAction(Character &chara);
        SDL_Rect eRect;

        int ePos;
        enemId id;
        enemAttributes attributes;
        vector<possibleActions> possibilities;
};
Enemy enemy_init(enemId id_, int initPos);
