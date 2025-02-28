#include "character.h"
#include "../game.h"

extern Game game;

double Character::maxHealth = 1.0;
int Character::energy = 3;
int Character::health = 1; //static

std::vector<cardIdInv> Character::cardInventoryId = {
    strike, strike, strike, defend, defend
};

Character::Character(int health_) : Gui(120, 220, 280, 200)
{
    maxHealth = health_;
    health = health_;
}

Character Character::init(int health_)
{
    Character profile(health_);
    return profile;
}

void Character::display_block()
{
    SDL_Rect chBlockBar{rect.x+65, 440, 220*(block/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 100, 150, 200, 100);
    SDL_RenderFillRect(game.renderer, &chBlockBar);
}

void Character::display_hp()
{
    SDL_Rect chHealthBar{rect.x+65, 440, 220*(health/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 100);
    SDL_RenderFillRect(game.renderer, &chHealthBar);
}

void Character::character_display()
{
    display_hp();
    display_block();
    game.render_img("assets/character/ironclad.png", rect.x, rect.y, rect.w, rect.h, NULL);
}

void Character::gain_block(int amount)
{
    block += amount;
}

void Character::take_damge(int dmg)
{
    if (dmg >= block) 
    {
        block = 0;
        dmg -= block;
        std::cout << "You no more block! Pass through: "  << dmg << std::endl;
        health -= dmg;
    }
    else 
    {
        block -= dmg;
    }
}
