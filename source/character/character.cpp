#include "character.h"
#include "../game.h"

extern Game game;

int Character::health = 0;
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

std::vector<cardId> Character::cardInventoryId = {
    cardId::strike, cardId::strike, cardId::strike, cardId::defend, cardId::defend
};
