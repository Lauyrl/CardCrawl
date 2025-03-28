#include "deck.h" //using namespace std; included i think

size_t Deck::maxSize = 0; //size needs to be static and defined here or it breaks
Deck::Deck(int maxSize_) { maxSize = maxSize_; }

void Deck::set_up_piles()
{
    renew();
    vector<cardId> copy = idInventory;
    shuffle_vector(copy);
    drawPile.resize(copy.size());
    for (size_t i{0}; i < copy.size(); i++)
    {
        drawPile[i] = Card(copy[i], i);
        cout << "Added card " << i << " to draw pile" << endl;
    }
    scrollVal = 1;
}

void Deck::renew()
{
    drawPile.clear(); hand.clear(); discardPile.clear();
    selectedIdx = NULL_CARD; usedIdx = NULL_CARD;
}

void Deck::renew_inventory()
{
    inventory.clear();
    inventory.resize(idInventory.size());
    for (size_t i{0}; i < idInventory.size(); i++) inventory[i] = Card(idInventory[i], i);
    scrollVal = 1;
}

void Deck::display_pile(vector<Card>& pile, int textType, bool move, bool highlight)
{
    SDL_Rect greyOut = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(game.renderer, 8, 8, 8, 80); SDL_RenderFillRect(game.renderer, &greyOut);
    scroll_val(scrollVal, 260*((pile.size()-1)/5)-100, 0);
    for (int i{0}; i < pile.size(); i++) pile[i].display_copy(252+200*(i%5), 150+260*(i/5)+scrollVal, move, highlight);
    scrollDirection = SCROLL_NULL;
    if      (textType == DC_TEXT)  pileLabel.render_text("                                       DISCARD PILE\nOnce full, cards are pushed back into draw pile\nAll cards currently in hand are discarded upon turn end");
    else if (textType == DP_TEXT)  pileLabel.render_text("                                       DRAW PILE\nOnce empty, cards are retrieved from discard pile\nEach turn, by default, 5 cards are drawn from the draw pile into hand");
    else if (textType == INV_TEXT) pileLabel.render_text("                                       INVENTORY");
    else                           pileLabel.render_text("                                       EVENT"); 
}

int Deck::interact_cards_event(bool inMenu, int textType)
{
    if (inMenu) return NULL_CARD;
    display_pile(inventory, textType, true, true);
    for (int i{0}; i < inventory.size(); i++) { if (inventory[i].detect_click()) return i; }
    return NULL_CARD;
}

void Deck::add_card(cardId id)
{
    idInventory.push_back(id);
    if (ironclad.check_relic(singing_bowl)) { ironclad.maxHealth += 2; ironclad.heal(2); }
}
