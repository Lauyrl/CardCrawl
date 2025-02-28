#include "deck.h"

size_t Deck::size = 0; //size needs to be static and defined here or it breaks
int Deck::selectedCardIndex = NULL_CARD;
std::vector<Card> Deck::hand;

//Deck reworked to no longer be considered GUI - 02/26
Deck::Deck(int size_)
{
    size = size_;
}

Deck deck_init(int size_)
{
    Deck deckObj(size_);
    return deckObj;
}

void Deck::set_up(Character character)
{
    for (size_t i{0}; i < size; i++)
    {
        Card base = card_init(character.cardInventoryId[i], i);
        add_card(base);
    }
}

void Deck::add_card(Card card)
{
    hand.push_back(card);
}

void Deck::remove_card()
{   
    if (hand.size() < 1) std::cerr << "Deck is empty.\n";
    hand.erase(hand.begin()+toRemove); size--;
    reformat_deck(hand, size);
    std::cout << "Consumed card " << toRemove << std::endl;
}

void reformat_deck(std::vector<Card> &cards, size_t newSize)
{
    for (size_t rePos{0}; rePos < newSize; rePos++) 
    {
        cards[rePos].reposition_in_deck(rePos);
    }
}

void Deck::select_card(int toSelect)
{
    if (toSelect != selectedCardIndex)
    {
        selectedCardIndex = toSelect;
        cout << "Selected card number " << toSelect << endl;
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
        std::cout << "Queried target: " << queried << std::endl;
        hand[selectedCardIndex].activate(chara, stage_enemies[queried]); //This can pass the 0th enemy if the target is a player (undefined if that one is dead)
        toRemove = selectedCardIndex;
        selectedCardIndex = NULL_CARD;
    }
}

void Deck::deck_iterate(int current, Character &chara, vector<Enemy> &stage_enemies)
{
    hand[current].card_display(hand[current].id, hand[current].pos);
    if (hand[current].detect_click()) 
    {
        select_card(current);
    }
    if (selectedCardIndex != NULL_CARD)
    {
        activate_card_process(chara, stage_enemies);
    }
}

