#include "deck.h" //using namespace std; included i think

size_t Deck::size = 0; //size needs to be static and defined here or it breaks
int Deck::selectedCardIdx = NULL_CARD;
vector<Card> Deck::hand;
vector<Card> Deck::drawPile;
vector<Card> Deck::discardPile;

Deck::Deck(int size_)
{
    size = size_;
}

void Deck::set_up(Character chara)
{
    for (size_t i{0}; i < size; i++)
    {
        Card card(chara.cardIdInventory[i], i);
        add_card(card);
    }
}

void Deck::add_card(Card card)
{
    hand.push_back(card);
}

void Deck::remove_card()
{   
    // if (hand.size() < 1) std::cerr << "Deck is empty.\n";
    if (toDiscard != NULL_CARD)
    {
        hand.erase(hand.begin()+toDiscard); size--;
        reformat();
        cout << "Consumed card " << toDiscard << endl;
    }
}

void Deck::reformat()
{
    for (size_t rePos{0}; rePos < size; rePos++) 
    {
        hand[rePos].reposition_in_deck(rePos);
    }
}

void Deck::select_card(int toSelect, int charaEnergy)
{
    if (charaEnergy >= hand[toSelect].attributes.cost && toSelect != selectedCardIdx)
    {
        if (selectedCardIdx != NULL_CARD) hand[selectedCardIdx].selected = false;
        selectedCardIdx = toSelect;
        hand[selectedCardIdx].selected = true;
        cout << "Selected card number " << toSelect << endl;
    }
    else 
    {
        cout << "Could not select card " << selectedCardIdx << endl;
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
        discardPile.push_back(hand[toDiscard]);
        selectedCardIdx = NULL_CARD;
    }
}

void Deck::iterate(int current, Character &chara, vector<Enemy> &stageEnemies)
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

