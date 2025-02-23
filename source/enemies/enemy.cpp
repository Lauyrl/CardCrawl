#include "enemy.h"

extern Game game;

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

void Enemy::enemy_display()
{
    game.render_img(eSpriteMap.at(id), 800, 200, 200, 200, NULL);
}
