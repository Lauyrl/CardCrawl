#include "../cards/deck.h"

double Character::maxHealth = 100.0;
int Character::health = 1; //static
int Character::gold = 10000;

vector<cardId> Character::cardIdInv = defaultCardIdInv;
Character::Character() : Gui(140, 300, 280, 200) {}
Character::Character(int health_) : Gui(140, 300, 280, 200)
{
    maxHealth = health_;
    health = health_;
}

void Character::display_block()
{
    SDL_Rect chBlockBar{rect.x+70, rect.y+200, 220*(block/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 180, 180, 180, 200);
    SDL_RenderFillRect(game.renderer, &chBlockBar);
    game.render_img("assets/character/block.png", rect.x+50, rect.y+182, 45, 45, 200, NULL);
    blockText.render_text(to_string(block));
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

void Character::display_energy()
{
    game.render_img("assets/ui/combat/red_energy.png", rect.x+70, rect.y+295, 100, 100, 180, NULL);
    string energyStr = to_string(energy) + "/3";
    energyText.render_text(energyStr);
}

void Character::lose_energy(int amount) { energy -= amount; }

void Character::reset_energy() { lose_energy(energy-3); }

void Character::reformat_relics() 
{
    int i{0}; 
    for (auto& relic:relicInv) { relic.second.move_rect(60*i-25, 30);  i++; }
}

void Character::heal (int amount)
{
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Character::gain_block(int amount) { block += amount; }

void Character::take_damage(int dmg)
{
    int totalDmg = dmg+dmg*((statuses[vulnerable].level>0)?1.25:1);
    dmgTextV.push_back(DmgText(totalDmg, rect.x+240, rect.y+30));
    slashfxV.push_back(SlashFX(rect.x+95, rect.y));
    hit = true;
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
    during_turn_relic_renew();
    combat_start_relic();
    for (auto& status:statuses) { status.second.level = 0; }
    if (check_relic(tea_set) && !relicInv[tea_set].active) { energy += 2; relicInv.at(tea_set).active = true; }
    slimedCnt = 0;
    flexUsed = 0;
    attackCardsUsed = 0;
}

void Character::renew_turn()
{
    if (slimedCnt) 
    {
        deck.discardPile.push_back(Card(slimed, deck.discardPile.size())); 
        deck.discardPile.push_back(Card(slimed, deck.discardPile.size())); 
    }
    reset_energy();
    during_turn_relic_renew();
    block = 0;
    slimedCnt = 0;
    attackCardsUsed = 0;
}

void Character::add_card(cardId id)
{
    cardIdInv.push_back(id);
    if (check_relic(singing_bowl)) { maxHealth += 2; heal(2); }
}
void Character::add_relic(relicId id)
{
    relicInv[id] = Relic(id);
    reformat_relics();
}
bool Character::check_relic(relicId id) { return (relicInv.find(id) != relicInv.end()); }
bool Character::check_relic_active(relicId id) { return check_relic(id) && relicInv.at(id).active; }

void Character::display_attacked_fx()
{
    if (dmgTextV.size() > 0)
    {
        if (dmgTextV.back().t < 60)
        {
            for (int i{0}; i < dmgTextV.size(); i++)//bad practice but i must man
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
            for (int i{0}; i < slashfxV.size(); i++)//bad practice but i must man
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
