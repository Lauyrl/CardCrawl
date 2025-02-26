#pragma once

#include "id_to_enemy.h"
#include "../gui/gui.h"

class Enemy : public Gui
{
    public:
        Enemy();
        Enemy(enemId id);
        void enemy_display(enemAttributes attributes_);
        void display_hp(enemAttributes attributes_);
        SDL_Rect eRect;

        int ePos;
        enemId id;
        enemAttributes attributes;
};

Enemy enemy_init(enemId id);
