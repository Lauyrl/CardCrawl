#pragma once

#include "id_to_enemy.h"
#include "../gui/gui.h"

const int NULL_ENEMY = -1;

class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemId id_, int initPos);
        void enemy_display(int pos);
        void display_hp();
        void take_damage(int damgeTaken);
        SDL_Rect eRect;

        int ePos;
        enemId id;
        enemAttributes attributes;
};

Enemy enemy_init(enemId id_, int initPos);
