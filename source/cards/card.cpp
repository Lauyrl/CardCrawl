#include "card.h"
#include "../game.h"

extern Game game;

Card::Card(cardIdInv id_, int initPos) : Gui(0, 0, 215, 285) 
{
    id = id_;
    pos = initPos;
    move_rect(START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y);
    attributes = attriMap.at(id);
}

Card card_init(cardIdInv id, int initPos)
{
    Card card = Card(id, initPos);
    return card;
}

void Card::card_display(cardIdInv id, int pos)
{
    game.render_img(cardSpriteMap.at(id), START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y, 210, 280, NULL);
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

int Card::query_target(vector<Enemy> stage_enemies, int numOfEnemies)
{
    for (size_t i{0}; i < numOfEnemies; i++)
    {
        if (stage_enemies[i].detect_cursor_hover(cursorX, cursorY) && process_click(clickQueued))
        {
            return i;
        }
    }
    return NULL_ENEMY;
}
