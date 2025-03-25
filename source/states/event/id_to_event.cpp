#include "event.h"

bool duplicator_pray_ef()
{
    int chosenCard = NULL_CARD; chosenCard = deck.interact_cards_event(panel.inMenu, 3);
    if (chosenCard != NULL_CARD)
    {
        ironclad.add_card(deck.inventory[chosenCard].id);
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
    game.eventInit = true;
    game.state_switch(Game::gameStates::map);
    return true;
}
bool gshrine_pray_ef() { ironclad.gold += 100; return true; }
bool cleric_heal_ef() { ironclad.gold -= 25; ironclad.heal(ironclad.maxHealth/4); return true; }
bool cleric_purify_ef() 
{
    int chosenCard = NULL_CARD; chosenCard = deck.interact_cards_event(panel.inMenu, 3);
    if (chosenCard != NULL_CARD)
    {
        ironclad.gold -= 50;
        ironclad.cardIdInv.erase(ironclad.cardIdInv.begin()+chosenCard);
        return true;
    }
    return false;
}

const map<choiceId, choiceAttributes> Choice::choiceAttriMap = {
    {duplicator_pray,  {1, "[Duplicate a card]", duplicator_pray_ef}},
    {leave,            {1, "[Leave]", leave_ef}},
    {bf_spirits_offer, {1, "[Offer a card]", bf_spririts_offer_ef}},
    {gshrine_pray,     {1, "[Pray]", gshrine_pray_ef}},
    {cleric_heal,      {1, "[Heal] Lose 35 Gold. Heal 25% Max HP", cleric_heal_ef}},
    {cleric_purify,    {1, "[Purify] Lose 50 Gold. Remove a card from your Deck", cleric_purify_ef}},
};
static vector<Choice> duplicatorV = { Choice(duplicator_pray, 0), Choice(leave, 1) };
static vector<Choice> bfSpiritsV  = { Choice(bf_spirits_offer, 0), Choice(leave, 1) };
static vector<Choice> gShrineV    = { Choice(gshrine_pray, 0), Choice(leave, 1) };
static vector<Choice> clericV     = { Choice(cleric_purify, -1), Choice(cleric_heal, 0), Choice(leave, 1) };

const map<eventId, eventAttributes> Event::evAttriMap = {
    {duplicator, {"assets/events/duplicator.png", "Duplicator", "Duplicate something buddy", duplicatorV, true}},
    {bf_spirits, {"assets/events/bonfire.jpg", "Bonfire Spirits", "Offer a card in exchange for heal", bfSpiritsV, true}},
    {gshrine   , {"assets/events/gold_shrine.jpg", "Golden Shrine", "Gain 100 Gold", gShrineV, true}},
    {cleric    , {"assets/events/cleric.jpg", "The Cleric", "You come across a bombastic, friendly cleric\nthat offers you his blessings", clericV, false}},
};
