#include "deck.h"

size_t Deck::size = 0;
int Deck::selectedCardIndex = NULL_CARD;
std::vector<Card> Deck::hand;

Deck::Deck(int size_) : Gui(DECK_REC_START_X, DECK_REC_START_Y, DECK_REC_WIDTH, DECK_REC_HEIGHT) 
{
    size = size_;
}

Deck deck_init(int size_)
{
    Deck deckObj = Deck(size_);
    return deckObj;
}

void Deck::set_up(Character character)
{
    int pos{0};
    for (size_t i{0}; i < size; i++)
    {
        Card base = card_init(character.cardInventoryId[i], pos);
        add_card(base);
        pos++;
    }
}

void Deck::add_card(Card card)
{
    hand.push_back(card);
}

void Deck::remove_card(int index)
{   
    if (hand.size() < 1) std::cerr << "Deck is empty.\n";
    hand.erase(hand.begin()+index); size--;
    reformat_deck(hand, size);
    std::cout << "Removed card " << index << std::endl;
}

void reformat_deck(std::vector<Card> &cards, size_t newSize)
{
    for (size_t rePos{0}; rePos < newSize; rePos++) 
    {
        cards[rePos].reposition_in_deck(rePos);
    }
}

