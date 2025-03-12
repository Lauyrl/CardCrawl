#include "card.h"

Card::Card() : Gui(CARD_POS_X_DEFAULT, CARD_POS_Y, 215, 285) 
{
    id = strike;
    pos = 0;
    move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pos, CARD_POS_Y);
    attributes = cAttriMap.at(id);
}

Card::Card(cardIdInv id_, int initPos) : Gui(CARD_POS_X_DEFAULT, CARD_POS_Y, 215, 285) //This is for sure off center
{
    id = id_;
    pos = initPos;
    move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pos, CARD_POS_Y);
    attributes = cAttriMap.at(id);
}

void Card::display()
{
    game.render_img(cSpriteMap.at(id), rect.x, rect.y, 210, 280, 255, NULL);
}

void Card::display_copy(int x, int y)
{
    game.render_img(cSpriteMap.at(id), x, y, 180, 240, 255, NULL);
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
    if (selected) rect.y = 571;
}

void Card::activate(vector<Enemy> &stageEnemies, int queried)
{
    auto it{cActionMap.find(id)};
    if (it == cActionMap.end()) cerr << "Action undefined " << endl;
    else 
    {
        it->second(stageEnemies, queried);
        selected = false;
    }
    ironclad.lose_energy(attributes.cost);
}

int Card::query_targetE(vector<Enemy> stageEnemies)
{
    for (size_t eIdx{0}; eIdx < stageEnemies.size(); eIdx++)
    {
        if (stageEnemies[eIdx].detect_click()) return eIdx;
    }
    return NULL_TARGET;
}

int Card::query_targetC()
{
    if (ironclad.detect_click()) return CHARACTER_TARGET;
    return NULL_TARGET;
}
