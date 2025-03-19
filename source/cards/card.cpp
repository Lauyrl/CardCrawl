#include "card.h"

Card::Card() : Gui(50+CARD_POS_X_DEFAULT, CARD_POS_Y, 125, 285) {}//{ attributes = cAttriMap.at(strike); }

Card::Card(cardId id_, int initPos) : Gui(50+CARD_POS_X_DEFAULT+STEP_INCREMENT*initPos, CARD_POS_Y, 125, 285) //This is for sure off center
{
    id = id_;
    pos = initPos;
    attributes = cAttriMap.at(id);
}

void Card::display_in_hand(int quantity)
{
    if (selected) rect.y = 571;
    rect.x = quantity*(STEP_INCREMENT-STEP_INCREMENT*(1.0-0.1*(quantity/4.0)))+760-80*quantity+STEP_INCREMENT*(1.0-0.1*(quantity*quantity/22.0))*pos;
    if (quantity != 0) game.render_img(attributes.sprite, rect.x-50, rect.y, 210, 280, 255, NULL);
}

void Card::display_copy(int x, int y, bool move, bool highlight)
{
    game.render_img(attributes.sprite, x, y, 180, 240, 255, NULL);
    if (move) rect = {x, y, 180, 240};
    if (highlight && detect_cursor_hover()) game.render_img("assets/ui/frame.png", rect.x-490, rect.y-310, rect.w+985, rect.h+750,255,NULL);
}

bool Card::highlight()
{
    if (detect_cursor_hover()  && rect.y > 575)        rect.y -= 52;
    if (!detect_cursor_hover() && rect.y < CARD_POS_Y) rect.y += 52;
    return detect_cursor_hover();
}

void Card::activate(vector<Enemy> &stageEnemies, int queried)
{
    attributes.action(stageEnemies, queried);
    selected = false;
    if (attributes.intent == Attack) ironclad.attackCardsUsed++;
    cout << "attack cards used: " << ironclad.attackCardsUsed << endl;
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
