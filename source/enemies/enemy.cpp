#include <iostream>
#include "enemy.h"

extern Game game;

Enemy::Enemy() : Gui(640, 200, 200, 200)
{}

Enemy::Enemy(enemId id_, int initPos) : Gui(640, 240, 200, 200)
{
    id = id_;
    ePos = initPos;
    possibilities = eActionMap.at(id);
    attributes = eAttriMap.at(id);
    move_rect(640+210*ePos, 240+(30*(ePos%2)));
}

Enemy enemy_init(enemId id_, int initPos)
{
    Enemy enemy = Enemy(id_, initPos);
    return enemy;
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

void Enemy::eAction(Character &chara)
{
    int value = rand() % 100;
    for (size_t i{0}; i < possibilities.size(); i++)
    {
        if (value <= possibilities[i].actionValue) 
        {
            possibilities[i].action(chara, *this);
            break;
        }
    }
}
