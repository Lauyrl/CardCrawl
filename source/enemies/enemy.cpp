#include "enemy.h"

Enemy::Enemy() : Gui(ENEMY_POS_X, ENEMY_POS_Y, 150, 150) {}
Enemy::Enemy(enemyId id_, int pos_, int x) : Gui(ENEMY_POS_X, ENEMY_POS_Y, 150, 150), id(id_), pos(pos_)
{
    attributes = eAttriMap.at(id);
    maxHealth = attributes.hp;
    size = attributes.size;
    rect = {x, ENEMY_POS_Y+(30*(pos%2))-100*size, 150+100*size, 150+100*size};
    origin = rect;
}

void Enemy::display()
{
    if (hit) shake();
    game.render_img(attributes.sprite, rect.x, rect.y, rect.w, rect.h, 255, NULL);
    display_hp();
    if (block > 0) display_block();
    display_intent();
    display_statuses();
    display_attacked_fx();
}

void Enemy::display_hp()
{
    SDL_Rect eHealthBar{rect.x, rect.y+160+100*size, (140+100*size)*(attributes.hp/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 240);
    SDL_RenderFillRect(game.renderer, &eHealthBar);
    healthText = Text(15, rect.x+50+50*size, rect.y+155+100*size, 255, 255, 255);
    healthText.render_text(to_string((int)attributes.hp)+'/'+to_string((int)maxHealth));
}

void Enemy::display_block()
{
    SDL_Rect chBlockBar{rect.x, rect.y+160+100*size, (140+100*size)*(block/maxHealth), 10};
    SDL_SetRenderDrawColor(game.renderer, 180, 180, 180, 200);
    SDL_RenderFillRect(game.renderer, &chBlockBar);
    game.render_img("assets/character/block.png", rect.x-23, rect.y+140+100*size, 45, 45, 200, NULL);
    blockText = Text(22, rect.x-9, rect.y+149+100*size, 140, 30, 0);
    blockText.render_text(to_string(block));
}

void Enemy::display_statuses()
{
    int i{0};
    for (auto& status:statuses)
    {
        if(status.second.level != 0) 
        {
            status.second.move_rect(rect.x+30*i-3, rect.y+170+100*size);
            status.second.display();
            i++;
        }
    }
}

void Enemy::display_intent() { intentUI.display(rect.x+55*size, rect.y+(13*size*size)); }

void Enemy::generate_intent(int turn)
{
    Action generated = attributes.alg(*this, turn); 
    intentUI = Intent(generated.intentId);
    intended = generated.action;
}

bool Enemy::action()
{
    tick++; int t = tick;
    if (t == 1) 
    { 
        intended(*this); 
        renew_turn();
        return false; 
        
    }
    else 
    {
        rect.x = ENEMY_POS_X+210*pos-(-t*t+10*t);
        healthText.tRect.x = rect.x+50+50*size-(-0.2*t*t+2*t);
        if (t == 14) 
        {
            rect = origin;
            tick = 0;
            return true;
        }
    }
    return false;
}

void Enemy::renew_turn()
{
    if (statuses[metallicize].level > 0) block += statuses[metallicize].level;
}

void Enemy::decrement_statuses()
{
    for (auto& status:statuses)
    {
        if (decrementableStatuses.find(status.first) != decrementableStatuses.end() && status.second.level > 0)
            status.second.level--;
    }
    statuses[malleable].value = 0;
}

void Enemy::cleanse()
{
    for (auto& status:statuses)
    {
        if (debuffs.find(status.first) != debuffs.end() && status.second.level > 0)
            status.second.level = 0;
    } 
}

void Enemy::heal(int amount)
{
    attributes.hp += amount;
    if (attributes.hp > maxHealth) attributes.hp = maxHealth;
}

void Enemy::gain_block(int amount) { block += amount; }

void Enemy::take_damage(int amount, int delay)
{
    int totalAmount = amount*(((statuses[vulnerable].level>0)?1.25:1)-((ironclad.statuses[weakness].level>0)?0.25:0))+ironclad.statuses[strength].level;
    if (statuses[intangible].level>0) totalAmount = 1;
    if (totalAmount >= block) 
    {
        totalAmount -= block;
        block = 0;
        attributes.hp -= totalAmount;
    }
    else block -= totalAmount;
    if (statuses[malleable].level>0) { block += (statuses[malleable].level + statuses[malleable].value); statuses[malleable].value++; }
    dmgTextV.push_back(DmgText(totalAmount, rect.x, rect.y+rect.h-175-(-size*size+10*size), delay));
    slashfxV.push_back(SlashFx(rect.x-20+50*size, rect.y+rect.h-175-(-size*size+10*size), delay));
    hit = true;
}

void Enemy::deal_damage(int dmg, int delay)
{
    ironclad.take_damage(dmg*((statuses[weakness].level>0)?0.75:1)+statuses[strength].level, delay);
    if (ironclad.check_relic(bronze_scales)) take_damage(3);
}

void Enemy::display_attacked_fx()
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

void Enemy::shake()
{
    if (shakeT < 6) {shakeT++; rect.x += shakeT*cos(2*shakeT); }
    else { shakeT = 0; hit = false; rect.x = origin.x; }
}
