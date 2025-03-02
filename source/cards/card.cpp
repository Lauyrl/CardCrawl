#include "card.h"
#include "../game.h"

extern Game game;

const int CHARACTER_TARGET = 0;

Card::Card(cardIdInv id_, int initPos) : Gui(START_LOC_X, DEFAULT_Y, 215, 285) //This is for sure off center
{
    id = id_;
    pos = initPos;
    move_rect(START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y);
    attributes = attriMap.at(id);
}

void Card::card_display()
{
    game.render_img(cardSpriteMap.at(id), rect.x, rect.y, 210, 280, NULL);
}

void Card::highlight()
{
    if (detect_cursor_hover() && rect.y > 575)
    {
        rect.y -= 52;
    }
    if (!detect_cursor_hover() && rect.y < DEFAULT_Y)
    {
        rect.y += 52;
    }
}

void Card::activate(Character &chara, Enemy &enemy)
{
    auto it{actionMap.find(id)};
    if (it == actionMap.end()) cerr << "Action undefined " << endl;
    else actionMap.at(id)(chara, enemy);
    chara.lose_energy(attributes.energyCost);
}

void Card::reposition_in_deck(int rePos)
{
    pos = rePos;
    move_rect(START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y);
}

int Card::query_targetE(vector<Enemy> stage_enemies)
{
    for (size_t eIndex{0}; eIndex < stage_enemies.size(); eIndex++)
    {
        if (stage_enemies[eIndex].detect_click()) return eIndex;
    }
    return NULL_TARGET;
}

int Card::query_targetC(Character chara)
{
    if (chara.detect_click()) return CHARACTER_TARGET;
    return NULL_TARGET;
}
