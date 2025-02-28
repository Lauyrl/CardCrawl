#include "card.h"
#include "../game.h"

extern Game game;

const int CHARACTER_TARGET = 0;

Card::Card(cardIdInv id_, int initPos) : Gui(0, 0, 215, 285) 
{
    id = id_;
    pos = initPos;
    move_rect(START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y);
    attributes = attriMap.at(id);
}

Card card_init(cardIdInv id, int initPos)
{
    Card card(id, initPos);
    return card;
}

void Card::card_display(cardIdInv id, int pos)
{
    game.render_img(cardSpriteMap.at(id), rect.x, rect.y, 210, 280, NULL);
}

void Card::activate(Character &chara, Enemy &enemy)
{
    auto it{actionMap.find(id)};
    if (it == actionMap.end()) cout << "Action undefined" << endl;
    else actionMap.at(id)(chara, enemy);
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
        if (stage_enemies[eIndex].detect_click())
        {
            return eIndex;
        }
    }
    return NULL_TARGET;
}

int Card::query_targetC(Character chara)
{
    if (chara.detect_click()) return CHARACTER_TARGET;
    return NULL_TARGET;
}
