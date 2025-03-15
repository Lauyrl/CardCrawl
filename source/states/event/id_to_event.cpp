#include "event.h"

bool duplicator_pray_ef()
{
    deck.display_pile(deck.drawPile, 3, true);
    int chosenCard = deck.interact_cards_event();
    if (chosenCard != NULL_CARD)
    {
        ironclad.cardIdInventory.push_back(deck.drawPile[chosenCard].id);
        return true;
    }
    return false;
}
bool leave_ef()
{
    cout << "tesssssssssst" << endl;
    game.eventInit = true;
    game.state_switch(Game::gameStates::map);
    return true;
}
const map<choiceId, choiceAttributes> Choice::choiceAttriMap = {
    {duplicator_pray, {1, "test", duplicator_pray_ef}},
    {leave,           {1, "leave", leave_ef}}
};


static vector<Choice> duplicatorVector = {
    Choice(duplicator_pray, 0), Choice(leave, 1)
};

const map<eventId, eventAttributes> Event::evAttriMap = {
    {duplicator ,{"assets/ui/event/e_duplicator.png", "duplicator", "Test test teset", duplicatorVector}}
};
