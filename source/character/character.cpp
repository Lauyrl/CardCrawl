#include "character.h"
#include "../game.h"

extern Game game;

int Character::health = 0; //static
Character::Character(int health_) : Gui(1,1,1,1)
{
    health = health_;
}

Character Character::init(int health_)
{
    Character profile = Character(health_);
    return profile;
}

void Character::character_display()
{
    
}

std::vector<cardIdInv> Character::cardInventoryId = {
    strike, strike, strike, strike, strike
};
