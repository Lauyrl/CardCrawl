#pragma once

#include "id_to_enemy.h"
#include "../gui/gui.h"

class Enemy : public Gui
{
    public:
        Enemy(enemId id);
        void enemy_display();
        SDL_Rect eRect;

        enemId id;
        enemAttributes attributes;
};

Enemy enemy_init(enemId id);
