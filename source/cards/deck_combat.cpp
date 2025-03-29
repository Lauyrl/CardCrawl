#include "deck.h"

void Deck::renew_hand()
{
    discard_hand();
    build_hand();
}

void Deck::discard_hand()
{
    selectedIdx = NULL_CARD; highlightedIdx = NULL_CARD; usedIdx = NULL_CARD;
    for (size_t i{0}; i < hand.size() ; i++)
    {
        if ( hand[i].id == burn) ironclad.take_damage(2);
        if (!hand[i].attributes.ethereal) discardPile.push_back(hand[i]);
        cout << "Cleared card " << i << endl;
    }
    hand.clear();
}

void Deck::refill_draw_pile()
{
    if (drawPile.size() == 0)
    {
        shuffle_vector(discardPile);
        drawPile = discardPile;
        discardPile.clear();
    }
}

void Deck::build_hand() { for (int i{0}; i < maxSize; i++) draw_card(); }

void Deck::hand_process(bool inMenu, vector<Enemy>& stageEnemies)
{
    usedIdx = NULL_CARD;
    for (size_t current{0}; current < hand.size(); current++)
    {
        if (hand[current].highlight()) highlightedIdx = current;
        hand[current].display_in_hand(hand.size(), current);   
        if (!inMenu) interact_card(current, stageEnemies); 
    }
    if (usedIdx != NULL_CARD) discard_used();

    if (selectedIdx != NULL_CARD) hand[selectedIdx].display_in_hand(hand.size(), selectedIdx);
    if (highlightedIdx != NULL_CARD)
    {
        hand[highlightedIdx].display_in_hand(hand.size(), highlightedIdx);
        highlightedIdx = NULL_CARD;
    }

    for (int i{0}; i < drawCards; i++) draw_card();
    drawCards = 0;
}

void Deck::discard_used()
{   
    if (usedIdx != NULL_CARD)
    {
        if (!hand[usedIdx].attributes.exhaust) discardPile.push_back(hand[usedIdx]);
        hand.erase(hand.begin() + usedIdx);
        cout << "Consumed card: " << usedIdx << endl;
    }
}

void Deck::interact_card(int current, vector<Enemy> &stageEnemies)
{
    if (hand[current].detect_click()) select_card(current);
    if (selectedIdx != NULL_CARD) query_and_activate_card_process(stageEnemies); //SlCI is NULL_CARD after activation adn by default
}

void Deck::select_card(int toSelect)
{
    if (ironclad.energy >= hand[toSelect].attributes.cost && toSelect != selectedIdx)
    {
        if (selectedIdx != NULL_CARD) hand[selectedIdx].selected = false;
        selectedIdx = toSelect;
        hand[selectedIdx].selected = true;
        cout << "Selected card number: " << toSelect << endl;
    }
    else 
    {
        cout << "Unselected card/Could not select card: " << selectedIdx << endl;
        if (selectedIdx != NULL_CARD) hand[selectedIdx].selected = false;
        selectedIdx = NULL_CARD;
    }
}

void Deck::query_and_activate_card_process(vector<Enemy> &stageEnemies)
{
    int queried = NULL_TARGET;
    if (hand[selectedIdx].attributes.intent == Attack) 
        queried = hand[selectedIdx].query_targetE(stageEnemies);
    else 
        queried = hand[selectedIdx].query_targetC();
    if (queried != NULL_TARGET)
    {
        cout << "Queried target: " << queried << endl;
        hand[selectedIdx].activate(stageEnemies, queried); //This passes the 0th enemy if the target is Character, can cause unintended behavior
        usedIdx = selectedIdx;
        selectedIdx = NULL_CARD;
        highlightedIdx = NULL_CARD;
    }
}

void Deck::draw_card()
{
    refill_draw_pile();
    if (drawPile.size() > 0)
    {
        hand.push_back(Card(drawPile.front().id));
        if (drawPile.front().id == the_void) ironclad.lose_energy(1);
        hand.back().selected = false;
        hand.back().rect.y = CARD_POS_Y + 156;
        drawPile.erase(drawPile.begin());
    }
}
