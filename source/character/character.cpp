#include "../cards/deck.h"

Character::Character() : Gui(140, 300, 280, 200) {}
Character::Character(int health_) : Gui(140, 300, 280, 200), maxHealth(health_), health(health_) {}

void Character::display(bool info)
{
    if (hit) shake();
    game.render_img("assets/character/ironclad.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
    if (info) 
    {
        display_hp();
        if (block > 0) display_block();
        display_statuses();
        healthText.render_text(to_string(health)+"/"+to_string((int)maxHealth));
        display_attacked_fx();
    }
}

void Character::display_hp()
{
    SDL_Rect chHealthBar{rect.x+70, rect.y+200, 220*(health/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 240);
    SDL_RenderFillRect(game.renderer, &chHealthBar);
}

void Character::display_block()
{
    SDL_Rect chBlockBar{rect.x+70, rect.y+200, 220*(block/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 180, 180, 180, 200);
    SDL_RenderFillRect(game.renderer, &chBlockBar);
    game.render_img("assets/character/block.png", rect.x+50, rect.y+182, 45, 45, 200, NULL);
    blockText.render_text(to_string(block));
}

void Character::display_statuses()
{
    int i{0};
    for (auto& status:statuses)
    {
        if(status.second.level != 0) 
        {
            status.second.move_rect(67+rect.x+30*i, rect.y+210);
            status.second.display();
            i++;
        }
    }
}

void Character::display_energy()
{
    game.render_img("assets/ui/combat/red_energy.png", rect.x+70, rect.y+295, 100, 100, 180, NULL);
    string energyStr = to_string(energy) + "/3";
    energyText.render_text(energyStr);
}

void Character::lose_energy(int amount) { energy -= amount; }

void Character::heal(int amount)
{
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Character::gain_block(int amount) { block += amount; }

void Character::take_damage(int amount, int delay)
{
    if (check_relic_active(fossil_helix)) { relicInv.at(fossil_helix).active = false; return; }
    int totalAmount = amount+amount*((statuses[vulnerable].level>0)?1.25:1);
    if (statuses[intangible].level>0) totalAmount = 1;
    if (totalAmount >= block) 
    {
        totalAmount -= block;
        block = 0;
        health -= totalAmount;
    }
    else block -= totalAmount;
    dmgTextV.push_back(DmgText(totalAmount, rect.x+240, rect.y+30, delay));
    slashfxV.push_back(SlashFx(rect.x+95, rect.y, delay));
    hit = true;
}

void Character::variables_reset() { 
    energy = 3; flexCnt = 0; attackCardsCnt = 0; 
    slimedCnt = 0; burnCnt = 0; voidCnt = 0;
    raged = false;
}

void Character::renew()
{
    block = 0;
    variables_reset();
    during_turn_relic_renew();
    for (auto& status:statuses) { status.second.level = 0; }
}

void Character::renew_turn()
{
    for (int i{0}; i < slimedCnt*2; i++) { deck.discardPile.push_back(Card(slimed)); }
    for (int i{0}; i < burnCnt*2; i++) { deck.discardPile.push_back(Card(burn)); }
    for (int i{0}; i < voidCnt; i++) { deck.discardPile.push_back(Card(the_void)); }
    variables_reset();
    during_turn_relic_renew();
}

void Character::add_relic(relicId id)
{
    relicInv[id] = Relic(id);
    reformat_relics();
}
void Character::reformat_relics() 
{
    int i{0}; 
    for (auto& relic:relicInv) { relic.second.move_rect(60*i+8, 30);  i++; }
}
bool Character::check_relic(relicId id) { return (relicInv.find(id) != relicInv.end()); }
bool Character::check_relic_active(relicId id) { return check_relic(id) && relicInv.at(id).active; }

void Character::display_attacked_fx()
{
    if (dmgTextV.size() > 0)
    {
        if (dmgTextV.back().t < 60)
        {
            for (int i{0}; i < dmgTextV.size(); i++)//bad practice but i must
            {
                if (dmgTextV[i].display()) dmgTextV.erase(dmgTextV.begin()+i); 
            }
        }
        else dmgTextV.clear();
    }
    if (slashfxV.size() > 0)
    {
        if (slashfxV.back().t < 12)
        {
            for (int i{0}; i < slashfxV.size(); i++)//bad practice but i must
            {
                if (slashfxV[i].display()) slashfxV.erase(slashfxV.begin()+i); 
            }
        }
        else slashfxV.clear();
    }
}

void Character::shake()
{
    if (shakeT < 6) {shakeT++; rect.x += shakeT*cos(2*shakeT); }
    else { shakeT = 0; hit = false; rect.x = 140; }
}
