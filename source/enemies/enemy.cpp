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
    game.render_img(attributes.sprite, rect.x, rect.y, 150, 150, 255, NULL);
    display_intent();
    display_hp();
    if (attacked)
    {
        slashfxT++;
        if (slashfxT < 12) slashfx.display(slashfxT, rect.x, rect.y);
        else if (slashfxT == 12) { attacked = false; slashfxT = 0; }
    }
}

void Enemy::display_hp()
{
    SDL_Rect eHealthBar{rect.x, rect.y+160, 140*(attributes.hp/eAttriMap.at(id).hp), 10};
    SDL_SetRenderDrawColor(game.renderer, 200, 0, 0, 240);
    SDL_RenderFillRect(game.renderer, &eHealthBar);
    healthText.render_text(to_string((int)attributes.hp)+'/'+to_string((int)eAttriMap.at(id).hp));
}

void Enemy::display_intent()
{
    intentUI.display();
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

void Enemy::take_damage(int dmgTaken)
{
    attacked = true; slashfxT = 0;
    int totalDmgTaken = dmgTaken+ironclad.statuses[strength].level*ironclad.statuses[strength].value;
    attributes.hp -= totalDmgTaken;
    cout << totalDmgTaken << endl;
}

void Enemy::deal_damage(int dmg)
{
    ironclad.take_damage(dmg);
    if (ironclad.check_relic(bronze_scales)) take_damage(3);
}


SlashFX::SlashFx() {}
void SlashFX::display(int t, int x, int y)
{
    game.render_img("assets/slash_vfx.png", x+190/24*t+10, y+220/24*t+10, -1.2*t*t+18*t+12, -1.2*t*t+18*t+12, 255, NULL);
}
