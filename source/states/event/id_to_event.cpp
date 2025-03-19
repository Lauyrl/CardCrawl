#include "event.h"

bool duplicator_pray_ef()
{
    int chosenCard = NULL_CARD; chosenCard = deck.interact_cards_event(panel.inMenu, 3);
    if (chosenCard != NULL_CARD)
    {
        ironclad.cardIdInv.push_back(deck.inventory[chosenCard].id);
        return true;
    }
    return false;
}

bool bf_spririts_offer_ef()
{
    int chosenCard = NULL_CARD; chosenCard = deck.interact_cards_event(panel.inMenu, 3);
    if (chosenCard != NULL_CARD)
    {
        ironclad.cardIdInv.erase(ironclad.cardIdInv.begin()+chosenCard);
        ironclad.heal(10);
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
    {duplicator_pray,  {1, "[Duplicate a card]", duplicator_pray_ef}},
    {leave,            {1, "[Leave]", leave_ef}},
    {bf_spirits_offer, {1, "[Offer a card]", bf_spririts_offer_ef}}
};

static vector<Choice> duplicatorVector = { Choice(duplicator_pray, 0), Choice(leave, 1) };
static vector<Choice> bfSpiritsVector  = { Choice(bf_spirits_offer, 0), Choice(leave, 1) };


const map<eventId, eventAttributes> Event::evAttriMap = {
    {duplicator, {"assets/events/duplicator.png", "Duplicator", "Duplicate something buddy", duplicatorVector, true}},
    {bf_spirits, {"assets/events/bonfire.jpg", "Bonfire Spirits", "Offer a card in exchange for heal", bfSpiritsVector, true}}
};
