#include "deck.h"

void Deck::renew_hand()
{
    selectedIdx = NULL_CARD;
    discard_hand();
    refill_draw_pile();
    build_hand();
}

void Deck::discard_hand()
{
    for (size_t i{0}; i < hand.size() ; i++)
    {
        discardPile.push_back(hand[i]);
        cout << "Cleared card " << i << endl;
    }
    hand.clear();
}

void Deck::refill_draw_pile()
{
    if (drawPile.size() == 0)
    {
        drawPile = discardPile;
        discardPile.clear();
    }
}

void Deck::build_hand()
{
    shuffle_vector(drawPile);
    hand.resize((drawPile.size()<maxSize) ? drawPile.size() : maxSize);
    for (int i{(drawPile.size()<maxSize) ? drawPile.size()-1 : maxSize-1}; i >= 0 ; i--)
    {
        hand[i] = Card(drawPile[i].id, i);
        hand[i].selected = false;
        drawPile.erase(drawPile.begin()+i);
    }
}

void Deck::reformat_hand()
{
    for (size_t rePos{0}; rePos < hand.size(); rePos++) hand[rePos].pos = rePos;
}

void Deck::hand_process(bool inMenu, vector<Enemy>& stageEnemies)
{
    usedIdx = NULL_CARD;
    for (size_t current{0}; current < hand.size(); current++)
    {
        if (hand[current].highlight()) highlightedIdx = current;
        hand[current].display_in_hand(hand.size());   
        if (!inMenu) interact_card(current, stageEnemies); 
    }
    if (usedIdx != NULL_CARD) discard_used();

    if (selectedIdx != NULL_CARD) hand[selectedIdx].display_in_hand(hand.size());
    if (highlightedIdx != NULL_CARD)
    {
        hand[highlightedIdx].display_in_hand(hand.size());
        highlightedIdx = NULL_CARD;
    }
    for (int i{0}; i < drawCards; i++) draw_card();
    drawCards = 0;
}

void Deck::discard_used()
{   
    // if (hand.size() < 1) std::cerr << "Deck is empty.\n";
    if (usedIdx != NULL_CARD)
    {
        if (!hand[usedIdx].attributes.exhaust) discardPile.push_back(hand[usedIdx]);
        hand.erase(hand.begin() + usedIdx);
        reformat_hand();
        cout << "Consumed card: " << usedIdx << endl;
    }
}

void Deck::draw_card()
{
    refill_draw_pile();
    if (drawPile.size() > 0)
    {
        int chosen = rand_int(0, drawPile.size()-1);
        hand.push_back(Card(drawPile[chosen].id, 0));
        reformat_hand();
        hand.back().rect.y -= 208;
        drawPile.erase(drawPile.begin()+chosen);
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
    }
}
