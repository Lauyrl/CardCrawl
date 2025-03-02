#include <iostream>
#include "enemy.h"

extern Game game;

Enemy::Enemy() : Gui(ENEMY_POS_X, ENEMY_POS_Y, 200, 200) {}

Enemy::Enemy(enemId id_, int initPos) : Gui(ENEMY_POS_X, ENEMY_POS_Y, 200, 200)
{
    id = id_;
    ePos = initPos;
    possibilities = eActionMap.at(id);
    attributes = eAttriMap.at(id);
    move_rect(ENEMY_POS_X+210*ePos, ENEMY_POS_Y+(30*(ePos%2)));
}

void Enemy::enemy_display()
{
    game.render_img(eSpriteMap.at(id), rect.x, rect.y, 150, 150, NULL);
    display_hp();
}

void Enemy::display_hp()
{
    SDL_Rect healthBar{rect.x, rect.y+160, 140*(attributes.hp/eAttriMap.at(id).hp), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 100);
    SDL_RenderFillRect(game.renderer, &healthBar);
}

void Enemy::take_damage(int damgeTaken)
{
    attributes.hp -= damgeTaken;
}

bool Enemy::e_action(Character &chara)
{
    int t = game.timeDelta;
    if (t == 1)
    {
        int value = rand() % 100;
        for (size_t i{0}; i < possibilities.size(); i++)
        {
            if (value <= possibilities[i].actionValue) 
            {
                possibilities[i].action(chara, *this);
                return false;
            }
        }
    }
    else 
    {
        move_rect(ENEMY_POS_X+210*ePos - (-t*t+10*t), ENEMY_POS_Y+(30*(ePos%2))); // can create offset
        if (t == 14) 
        {
            move_rect(ENEMY_POS_X+210*ePos, ENEMY_POS_Y+(30*(ePos%2)));
            return true;
        }
    }
    return false;
}
