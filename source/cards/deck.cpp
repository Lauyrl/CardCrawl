#include "deck.h" //using namespace std; included i think

size_t Deck::maxSize = 0; //size needs to be static and defined here or it breaks
int Deck::selectedCardIdx = NULL_CARD;
vector<Card> Deck::hand;
vector<Card> Deck::drawPile;
vector<Card> Deck::discardPile;

Deck::Deck(int maxSize_)
{
    maxSize = maxSize_;
}

void Deck::set_up_draw_pile(Character chara)
{
    shuffle_vector(chara.cardIdInventory);
    drawPile.resize(chara.cardIdInventory.size());
    for (size_t i{0}; i < chara.cardIdInventory.size(); i++)
    {
        Card card(chara.cardIdInventory[i], i);
        add_card(drawPile, i, card);
        cout << "Added card " << i << " to draw pile" << endl;
    }
}

void Deck::build_hand()
{
    shuffle_vector(drawPile);
    hand.resize((drawPile.size()<maxSize) ? drawPile.size() : maxSize);
    for (int i{(drawPile.size()<maxSize) ? drawPile.size()-1 : maxSize-1}; i >= 0 ; i--)
    {
        add_card(hand, i, drawPile[i]);
        drawPile.erase(drawPile.begin()+i);
    }
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

void Deck::add_card(vector<Card> &pile, int idx, Card card)
{
    pile[idx] = card;
    pile[idx].pos = idx;
    pile[idx].move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pile[idx].pos, CARD_POS_Y);
    cout << "Added card " << idx << " to pile" << endl;
}

void Deck::discard_card()
{   
    // if (hand.size() < 1) std::cerr << "Deck is empty.\n";
    if (toDiscard != NULL_CARD)
    {
        hand.erase(hand.begin()+toDiscard);
        reformat_hand();
        cout << "Consumed card: " << toDiscard << endl;
    }
}

void Deck::reformat_hand()
{
    for (size_t rePos{0}; rePos < hand.size(); rePos++) 
    {
        hand[rePos].pos = rePos;
        hand[rePos].move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*hand[rePos].pos, CARD_POS_Y);
    }
}

void Deck::select_card(int toSelect, int charaEnergy)
{
    if (charaEnergy >= hand[toSelect].attributes.cost && toSelect != selectedCardIdx)
    {
        if (selectedCardIdx != NULL_CARD) hand[selectedCardIdx].selected = false;
        selectedCardIdx = toSelect;
        hand[selectedCardIdx].selected = true;
        cout << "Selected card number: " << toSelect << endl;
    }
    else 
    {
        cout << "Could not select card: " << selectedCardIdx << endl;
        if (selectedCardIdx != NULL_CARD) hand[selectedCardIdx].selected = false;
        selectedCardIdx = NULL_CARD;
    }
}

void Deck::activate_card_process(Character &chara, vector<Enemy> &stageEnemies)
{
    int queried = NULL_TARGET;
    if (hand[selectedCardIdx].attributes.intent == Attack) 
         queried = hand[selectedCardIdx].query_targetE(stageEnemies);
    else queried = hand[selectedCardIdx].query_targetC(chara);
    if (queried != NULL_TARGET)
    {
        cout << "Queried target: " << queried << endl;
        hand[selectedCardIdx].activate(chara, stageEnemies[queried]); //This passed the 0th enemy if the target is Character, can cause unintended behavior
        toDiscard = selectedCardIdx;
        selectedCardIdx = NULL_CARD;
    }
}

void Deck::interact_cards(int current, Character &chara, vector<Enemy> &stageEnemies)
{
    hand[current].highlight();
    if (hand[current].selected) hand[current].rect.y = 571;
    hand[current].display();
    if (hand[current].detect_click()) 
    {
        select_card(current, chara.energy);
    }
    if (selectedCardIdx != NULL_CARD) //SlCI is NULL_CARD after activation adn by default
    {
        activate_card_process(chara, stageEnemies);
    }
}

