#include "deck.h" //using namespace std; included i think

size_t Deck::size = 0; //size needs to be static and defined here or it breaks
int Deck::selectedCardIndex = NULL_CARD;
vector<Card> Deck::hand;
vector<Card> Deck::drawPile;
vector<Card> Deck::discardPile;

Deck::Deck(int size_)
{
    size = size_;
}

void Deck::set_up(Character character)
{
    for (size_t i{0}; i < size; i++)
    {
        Card card(character.cardInventoryId[i], i);
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
        reformat_deck();
        cout << "Consumed card " << toDiscard << endl;
    }
}

void Deck::reformat_deck()
{
    for (size_t rePos{0}; rePos < size; rePos++) 
    {
        hand[rePos].reposition_in_deck(rePos);
    }
}

void Deck::select_card(int toSelect, int charEnergy)
{
    if (charEnergy >= hand[toSelect].attributes.energyCost && toSelect != selectedCardIndex)
    {
        if (selectedCardIndex != NULL_CARD) hand[selectedCardIndex].selected = false;
        selectedCardIndex = toSelect;
        hand[selectedCardIndex].selected = true;
        cout << "Selected card number " << toSelect << endl;
    }
    else 
    {
        cout << "Could not select card " << selectedCardIndex << endl;
        if (selectedCardIndex != NULL_CARD) hand[selectedCardIndex].selected = false;
        selectedCardIndex = NULL_CARD;
    }
}

void Deck::activate_card_process(Character &chara, vector<Enemy> &stage_enemies)
{
    int queried = NULL_TARGET;
    if (hand[selectedCardIndex].attributes.intent == Attack) 
         queried = hand[selectedCardIndex].query_targetE(stage_enemies);
    else queried = hand[selectedCardIndex].query_targetC(chara);
    if (queried != NULL_TARGET)
    {
        cout << "Queried target: " << queried << endl;
        hand[selectedCardIndex].activate(chara, stage_enemies[queried]); //This passed the 0th enemy if the target is Character, can cause unintended behavior
        toDiscard = selectedCardIndex;
        discardPile.push_back(hand[toDiscard]);
        selectedCardIndex = NULL_CARD;
    }
}

void Deck::deck_iterate(int current, Character &chara, vector<Enemy> &stage_enemies)
{
    hand[current].highlight();
    if (hand[current].selected) hand[current].rect.y = 571;
    hand[current].card_display();
    if (hand[current].detect_click()) 
    {
        select_card(current, chara.energy);
    }
    if (selectedCardIndex != NULL_CARD) //SlCI is NULL_CARD after activation adn by default
    {
        activate_card_process(chara, stage_enemies);
    }
}

