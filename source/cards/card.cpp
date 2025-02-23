#include "card.h"
#include "../game.h"

extern Game game;

Card::Card(cardId id_, int cardPos) : Gui(0, 0, 215, 285) 
{
    id = id_;
    pos = cardPos;
    attributes = attriMap.at(id);
}

Card card_init(cardId id, int initPos)
{
    Card card = Card(id, initPos);
    card.move_rect(START_LOC_X+STEP_INCREMENT*initPos, DEFAULT_Y);
    return card;
}

void Card::card_display(cardId id, int pos)
{
    game.render_img(cardSpriteMap.at(id), START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y, 210, 280, NULL);
}

void Card::object_loop(int current, int &selectedCard, int &toRemove, Character chara, Enemy enemy)
{
    card_display(id, pos);
    if (detect_cursor_hover(cursorX, cursorY) && process_click(clickQueued)) 
    {
        assess_card(current, selectedCard, toRemove, chara, enemy);
    }
}
void Card::activate(Character chara, Enemy enemy)
{
    auto it{actionMap.find(id)};
    if (it == actionMap.end()) cout << "Action undefined" << endl;
    else actionMap.at(id)(chara, enemy);
    
}

void Card::assess_card(int assessed, int &selectedInDeck, int &toRemove, Character chara, Enemy enemy)
{
    if (assessed != selectedInDeck)
    {
        selectedInDeck = assessed;
        cout << "Selected card number " << assessed << endl;
    }
    else if (assessed == selectedInDeck)
    { 
        activate(chara, enemy); // implicitly this->activate()
        cout << "Activated card number " << pos 
        << ", energy spent: " << attributes.energyCost << endl;
        selectedInDeck = NULL_CARD;
        toRemove = assessed;
    }
}

void Card::reposition_in_deck(int rePos)
{
    pos = rePos;
    move_rect(START_LOC_X+STEP_INCREMENT*pos, DEFAULT_Y);
}

