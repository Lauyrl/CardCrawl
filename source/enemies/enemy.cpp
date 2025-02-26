#include <iostream>
#include "enemy.h"

extern Game game;

Enemy::Enemy() : Gui(800, 200, 200, 200)
{}

Enemy::Enemy(enemId id_) : Gui(800, 200, 200, 200)
{
    id = id_;
    attributes = eAttriMap.at(id_);
}

Enemy enemy_init(enemId id_)
{
    Enemy enemy = Enemy(id_);
    return enemy;
}

void Enemy::enemy_display(enemAttributes attributes_)
{
    display_hp(attributes_);
    game.render_img(eSpriteMap.at(id), 800, 200, 200, 200, NULL);
}

void Enemy::display_hp(enemAttributes attributes_)
{
    SDL_SetRenderDrawColor(game.renderer, 255, 0, 0, 100);
    SDL_Rect healthBar{800, 410, 200*(attributes_.hp/eAttriMap.at(id).hp), 10};
    SDL_RenderFillRect(game.renderer, &healthBar);
}
