#include "card.h"
#include "../game.h"

extern Game game;

Card::Card(cardIdInv id_, int initPos) : Gui(CARD_POS_X_DEFAULT, CARD_POS_Y, 215, 285) //This is for sure off center
{
    id = id_;
    pos = initPos;
    move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pos, CARD_POS_Y);
    attributes = cAttriMap.at(id);
}

void Card::display()
{
    game.render_img(cSpriteMap.at(id), rect.x, rect.y, 210, 280, NULL);
}

void Card::highlight()
{
    if (detect_cursor_hover() && rect.y > 575)
    {
        rect.y -= 52;
    }
    if (!detect_cursor_hover() && rect.y < CARD_POS_Y)
    {
        rect.y += 52;
    }
}

void Card::activate(Character &chara, Enemy &enemy)
{
    auto it{cActionMap.find(id)};
    if (it == cActionMap.end()) cerr << "Action undefined " << endl;
    else cActionMap.at(id)(chara, enemy);
    chara.lose_energy(attributes.cost);
}

void Card::reposition_in_deck(int rePos)
{
    pos = rePos;
    move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pos, CARD_POS_Y);
}

int Card::query_targetE(vector<Enemy> stageEnemies)
{
    for (size_t eIdx{0}; eIdx < stageEnemies.size(); eIdx++)
    {
        if (stageEnemies[eIdx].detect_click()) return eIdx;
    }
    return NULL_TARGET;
}

int Card::query_targetC(Character chara)
{
    if (chara.detect_click()) return CHARACTER_TARGET;
    return NULL_TARGET;
}
