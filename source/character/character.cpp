#include "character.h"

extern Game game;
double Character::maxHealth = 100.0;
int Character::energy = 3;
int Character::health = 1; //static

std::vector<cardIdInv> Character::cardIdInventory = {
    strike, strike, strike, strike, defend, defend, defend, iron_wave, iron_wave, iron_wave, strike, strike
};

Character::Character(int health_) : Gui(140, 300, 280, 200)
{
    maxHealth = health_;
    health = health_;
    energy = 3;
}

void Character::display_block()
{
    SDL_Rect chBlockBar{rect.x+70, rect.y+200, 220*(block/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 100, 150, 200, 100);
    SDL_RenderFillRect(game.renderer, &chBlockBar);
}

void Character::display_hp()
{
    SDL_Rect chHealthBar{rect.x+70, rect.y+200, 220*(health/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 100);
    SDL_RenderFillRect(game.renderer, &chHealthBar);
}

void Character::display()
{
    display_hp();
    display_block();
    game.render_img("assets/character/ironclad.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

void Character::display_energy()
{
    game.render_img("assets/ui/red_energy.png", rect.x-10, rect.y+240, 100, 100, 180, NULL);
    string energyStr = to_string(energy) + "/3";
    energyText.render_text(energyStr);
}

void Character::gain_block(int amount)
{
    block += amount;
    // cout << chara.block << ' ' << endl;
}

void Character::take_damge(int dmg)
{
    if (dmg >= block) 
    {
        block = 0;
        dmg -= block;
        // cout << "Shieldless! Pass through: "  << dmg << std::endl;
        health -= dmg;
        // cout << chara.health << ' ' << chara.block << ' ' << endl;
    }
    else 
    {
        block -= dmg;
        // cout << chara.health << ' ' << chara.block << ' ' << endl;
    }
}

void Character::lose_energy(int amount)
{
    energy -= amount;
}

void Character::reset_energy()
{
    lose_energy(energy-3);
}
