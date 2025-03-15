#include "card.h"

Card::Card() : Gui(CARD_POS_X_DEFAULT, CARD_POS_Y, 215, 285) 
{
    id = strike;
    pos = 0;
    attributes = cAttriMap.at(id);
}

Card::Card(cardIdInv id_, int initPos) : Gui(CARD_POS_X_DEFAULT+STEP_INCREMENT*initPos, CARD_POS_Y, 215, 285) //This is for sure off center
{
    id = id_;
    pos = initPos;
    attributes = cAttriMap.at(id);
}

void Card::display()
{
    if (selected) rect.y = 571;
    game.render_img(attributes.sprite, rect.x, rect.y, 210, 280, 255, NULL);
    if (rect.x != CARD_POS_X_DEFAULT+STEP_INCREMENT*pos && rect.y != CARD_POS_Y)
        move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pos, CARD_POS_Y);
}

void Card::display_copy(int x, int y, bool move)
{
    game.render_img(attributes.sprite, x, y, 180, 240, 255, NULL);
    if (move) rect = {x, y, 180, 240};
    if (detect_cursor_hover()) game.render_img("assets/ui/frame.png", rect.x-490, rect.y-310, rect.w+985, rect.h+750,255,NULL);
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

void Card::activate(vector<Enemy> &stageEnemies, int queried)
{
    attributes.action(stageEnemies, queried);
    selected = false;
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
