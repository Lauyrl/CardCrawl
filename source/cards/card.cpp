#include "deck.h"

Card::Card() : Gui(0, 200, 125, 285) {}
Card::Card(cardId id_) : Gui(0, 200, 125, 285), id(id_) { attributes = cAttriMap.at(id); }

void Card::display_in_hand(int quantity, int pos)
{
    if (selected) rect.y = 571;
    rect.x = quantity*(STEP_INCREMENT-STEP_INCREMENT*(1.0-0.1*(quantity/4.0)))+760-80*quantity+STEP_INCREMENT*(1.0-0.1*(quantity*quantity/22.0))*pos;
    if (quantity != 0) game.render_img(attributes.sprite, rect.x-50, rect.y, 210, 280, 255, NULL);
}

void Card::display_copy(int x, int y, bool highlight)
{
    rect = {x, y, 180, 240};
    game.render_img(attributes.sprite, x, y, rect.w, rect.h, 255, NULL);
    if (highlight && detect_cursor_hover()) game.render_img("assets/ui/frame.png", rect.x-490, rect.y-310, rect.w+985, rect.h+750,255,NULL);
}

bool Card::highlight()
{
    if ( detect_cursor_hover() && rect.y > 575)        rect.y -= 52;
    if (!detect_cursor_hover() && rect.y < CARD_POS_Y) rect.y += 52;
    if (!detect_cursor_hover() && rect.y > CARD_POS_Y) rect.y -= 52;
    return detect_cursor_hover();
}

void Card::activate(vector<Enemy> &stageEnemies, int queried)
{
    ironclad.lose_energy(attributes.cost);
    attributes.action(stageEnemies, queried);
    selected = false;
    if (attributes.intent == Attack) 
    {
        ironclad.attackCardsCnt++;
        if (ironclad.raged) ironclad.block += 3;
    }
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
