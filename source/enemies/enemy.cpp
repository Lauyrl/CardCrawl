#include "enemy.h"

Enemy::Enemy() : Gui(ENEMY_POS_X, ENEMY_POS_Y, 200, 200) {}

Enemy::Enemy(enemyId id_, int initPos) : Gui(ENEMY_POS_X, ENEMY_POS_Y, 200, 200)
{
    id = id_;
    pos = initPos;
    attributes = eAttriMap.at(id);
    move_rect(ENEMY_POS_X+210*pos, ENEMY_POS_Y+(30*(pos%2)));
    healthText = Text(15, rect.x+60, rect.y+155, 255, 255, 255);
}

void Enemy::display()
{
    if (hit) shake();
    game.render_img(attributes.sprite, rect.x, rect.y, 150, 150, 255, NULL);
    display_statuses();
    display_intent();
    display_hp();
    display_attacked_fx();
}

void Enemy::display_hp()
{
    SDL_Rect eHealthBar{rect.x, rect.y+160, 140*(attributes.hp/eAttriMap.at(id).hp), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 240);
    SDL_RenderFillRect(game.renderer, &eHealthBar);
    healthText.render_text(to_string((int)attributes.hp)+'/'+to_string((int)eAttriMap.at(id).hp));
}

void Enemy::display_intent() { intentUI.display(); }

void Enemy::display_statuses()
{
    int i{0};
    for (auto& status:statuses)
    {
        if(status.second.level != 0) 
        {
            status.second.move_rect(rect.x+30*i-3, rect.y+170);
            status.second.display();
            i++;
        }
    }
}

void Enemy::generate_intent()
{
    int value = rand_int(0, 100);
    for (size_t i{0}; i < attributes.actions.size(); i++)
    {
        if (value <= attributes.actions[i].actionValue) 
        {
            intended = attributes.actions[i].action;
            intentUI = Intent(attributes.actions[i].intentId, rect.x, rect.y);
            return;
        }
    }
}

bool Enemy::enemy_action()
{
    tick++; int t = tick;
    if (t == 1) { intended(*this); return false; }
    else 
    {
        move_rect(ENEMY_POS_X+210*pos - (-t*t+10*t), ENEMY_POS_Y+(30*(pos%2))); // can create offset
        healthText.tRect.x = rect.x+60 - (-0.2*t*t+2*t);

        if (t == 14) 
        {
            move_rect(ENEMY_POS_X+210*pos, ENEMY_POS_Y+(30*(pos%2)));
            healthText.tRect.x = rect.x+60;
            tick = 0;
            return true;
        }
    }
    return false;
}

void Enemy::decrement_statuses()
{
    for (auto& status:statuses)
    {
        if (decrementableStatuses.find(status.first) != decrementableStatuses.end() && status.second.level > 0)
            status.second.level--;
    }
}

void Enemy::take_damage(int dmgTaken)
{
    int totalDmgTaken = dmgTaken*(((statuses[vulnerable].level>0)?1.25:1)-((ironclad.statuses[weakness].level>0)?0.25:0))+ironclad.statuses[strength].level;
    dmgTextV.push_back(DmgText(totalDmgTaken, rect.x, rect.y+20));
    slashfxV.push_back(SlashFX(rect.x-20, rect.y));
    hit = true;
    attributes.hp -= totalDmgTaken;
    cout << totalDmgTaken << endl;
}

void Enemy::deal_damage(int dmg)
{
    ironclad.take_damage(dmg*((statuses[weakness].level>0)?0.75:1)+statuses[strength].level);
    if (ironclad.check_relic(bronze_scales)) take_damage(3);
}

void Enemy::display_attacked_fx()
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

void Enemy::shake()
{
    if (shakeT < 6) {shakeT++; rect.x += shakeT*cos(2*shakeT); }
    else { shakeT = 0; hit = false; rect.x = ENEMY_POS_X+210*pos; }
}
