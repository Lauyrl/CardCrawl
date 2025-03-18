#include "../cards/deck.h"

double Character::maxHealth = 100.0;
int Character::health = 1; //static
int Character::gold = 10000;

std::vector<cardIdInv> Character::cardIdInv = {
    strike, strike, strike, strike, strike, defend, defend, defend, iron_wave, iron_wave
};
Character::Character() : Gui(140, 300, 280, 200) {}
Character::Character(int health_) : Gui(140, 300, 280, 200)
{
    maxHealth = health_;
    health = health_;
}

void Character::display_block()
{
    SDL_Rect chBlockBar{rect.x+70, rect.y+200, 220*(block/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 100, 150, 200, 240);
    SDL_RenderFillRect(game.renderer, &chBlockBar);
}

void Character::display_hp()
{
    SDL_Rect chHealthBar{rect.x+70, rect.y+200, 220*(health/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 240);
    SDL_RenderFillRect(game.renderer, &chHealthBar);
}

void Character::display_statuses()
{
    int i{0};
    for (auto status:statuses)
    {
        if(status.second.level != 0) 
        {
            game.render_img(status.second.sprite, 68+rect.x+30*i, rect.y+210, 30, 30, 200, NULL);
            i++;
        }
    }
}

void Character::display()
{
    display_hp();
    display_block();
    display_statuses();
    game.render_img("assets/character/ironclad.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

void Character::display_energy()
{
    game.render_img("assets/ui/combat/red_energy.png", rect.x-10, rect.y+240, 100, 100, 180, NULL);
    string energyStr = to_string(energy) + "/3";
    energyText.render_text(energyStr);
}

void Character::lose_energy(int amount) { energy -= amount; }

void Character::reset_energy() { lose_energy(energy-3); }

void Character::reformat_relics() { for (int i{0}; i < relicInv.size(); i++) relicInv[i].move_rect(60*i-25, 30); }

void Character::heal (int amount)
{
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Character::gain_block(int amount)
{
    block += amount;
    // cout << chara.block << ' ' << endl;
}

void Character::take_damge(int dmg)
{
    int totalDmg = dmg+dmg*(statuses[vulnerable].value*statuses[vulnerable].level);
    //cout << totalDmg << endl;
    if (totalDmg >= block) 
    {
        block = 0;
        totalDmg -= block;
        health -= totalDmg;
    }
    else block -= totalDmg;
    // cout << chara.health << ' ' << chara.block << ' ' << endl;
}

void Character::renew()
{
    reset_energy();
    combat_start_relic_renew();
    for (auto& status:statuses) { status.second.level = 0; }
    flexEndTurnEffect = 0;
}
