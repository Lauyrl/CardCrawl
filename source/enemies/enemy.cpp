#include "enemy.h"

Enemy::Enemy() : Gui(ENEMY_POS_X, ENEMY_POS_Y, 200, 200) {}

Enemy::Enemy(enemyId id_, int initPos) : Gui(ENEMY_POS_X, ENEMY_POS_Y, 200, 200)
{
    id = id_;
    pos = initPos;
    attributes = eAttriMap.at(id);
    move_rect(ENEMY_POS_X+210*pos, ENEMY_POS_Y+(30*(pos%2)));
}

void Enemy::display()
{
    game.render_img(attributes.sprite, rect.x, rect.y, 150, 150, 255, NULL);
    display_hp();
}

void Enemy::display_hp()
{
    SDL_Rect eHealthBar{rect.x, rect.y+160, 140*(attributes.hp/eAttriMap.at(id).hp), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 240);
    SDL_RenderFillRect(game.renderer, &eHealthBar);
}

bool Enemy::enemy_action()
{
    tick++; int t = tick;
    if (t == 1)
    {
        int value = rand() % 100;
        for (size_t i{0}; i < attributes.actions.size(); i++)
        {
            if (value <= attributes.actions[i].actionValue) 
            {
                attributes.actions[i].action(*this);
                return false;
            }
        }
    }
    else 
    {
        move_rect(ENEMY_POS_X+210*pos - (-t*t+10*t), ENEMY_POS_Y+(30*(pos%2))); // can create offset
        if (t == 14) 
        {
            move_rect(ENEMY_POS_X+210*pos, ENEMY_POS_Y+(30*(pos%2)));
            tick = 0;
            return true;
        }
    }
    return false;
}

void Enemy::take_damage(int damageTaken)
{
    attributes.hp -= damageTaken;
    // cout << enemy.attributes.hp << ' ' << endl;
}
