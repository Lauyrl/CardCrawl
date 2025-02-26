#include <iostream>
#include "enemy.h"

extern Game game;

Enemy::Enemy() : Gui(800, 200, 200, 200)
{}

Enemy::Enemy(enemId id_, int initPos) : Gui(640, 200, 200, 200)
{
    rect = {640+210*initPos, 200, 200, 200};
    id = id_;
    attributes = eAttriMap.at(id_);
}

Enemy enemy_init(enemId id_, int initPos)
{
    Enemy enemy = Enemy(id_, initPos);
    return enemy;
}

void Enemy::enemy_display(int pos)
{
    display_hp();
    game.render_img(eSpriteMap.at(id), 640+210*pos, 200, 200, 200, NULL);
}

void Enemy::display_hp()
{
    SDL_Rect healthBar{rect.x, 410, 200*(attributes.hp/eAttriMap.at(id).hp), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 100);
    SDL_RenderFillRect(game.renderer, &healthBar);
}

void Enemy::take_damage(int damgeTaken)
{
    attributes.hp -= damgeTaken;
}
