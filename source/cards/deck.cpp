#include "deck.h" //using namespace std; included i think

size_t Deck::maxSize = 0; //size needs to be static and defined here or it breaks
Deck::Deck(int maxSize_) { maxSize = maxSize_; }

void Deck::set_up_piles()
{
    renew();
    vector<cardIdInv> copy = ironclad.cardIdInv;
    shuffle_vector(copy);
    drawPile.resize(copy.size());
    for (size_t i{0}; i < copy.size(); i++)
    {
        Card card(copy[i], i);
        add_card(drawPile, i, card);
        cout << "Added card " << i << " to draw pile" << endl;
    }
    scrollVal = 1;
}

void Deck::renew_inventory()
{
    inventory.clear();
    inventory.resize(ironclad.cardIdInv.size());
    for (size_t i{0}; i < ironclad.cardIdInv.size(); i++)
    {
        Card card(ironclad.cardIdInv[i], i);
        add_card(inventory, i, card);
    }
    scrollVal = 1;
}

void Deck::add_card(vector<Card> &pile, int idx, Card card)
{
    pile[idx] = card;
    pile[idx].pos = idx;
    pile[idx].move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pile[idx].pos, CARD_POS_Y);
    // cout << "Added card " << idx << " to pile" << endl;
}

void Deck::display_pile(vector<Card>& pile, int textType, bool move, bool highlight)
{
    SDL_Rect greyOut = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(game.renderer, 8, 8, 8, 80);
    SDL_RenderFillRect(game.renderer, &greyOut);
    scroll_val_lower(scrollVal, 260*((pile.size()-1)/5)-100);
    for (int i{0}; i < pile.size(); i++)
    {
        pile[i].display_copy(252+200*(i%5), 150+260*(i/5)+scrollVal, move, highlight);
    }
    scrollDirection = SCROLL_NULL;
    if (textType == DC_TEXT)  pileLabel.render_text("                                       DISCARD PILE\nOnce full, cards are pushed back into draw pile\nAll cards currently in hand are discarded upon turn end");
    else if (textType == DP_TEXT)  pileLabel.render_text("                                       DRAW PILE\nOnce empty, cards are retrieved from discard pile\nEach turn, by default, 5 cards are drawn from the draw pile into hand");
    else if (textType == INV_TEXT) pileLabel.render_text("                                       INVENTORY");
    else pileLabel.render_text("                                       EVENT"); 
}

int Deck::interact_cards_event(bool inMenu, int textType)
{
    if (inMenu) return NULL_CARD;
    display_pile(deck.inventory, textType, true, true);
    for (int i{0}; i < inventory.size(); i++) 
        if (inventory[i].detect_click()) return i;
    return NULL_CARD;
}

void Deck::renew()
{
    drawPile.clear(); hand.clear(); discardPile.clear();
    selectedIdx = NULL_CARD; usedIdx = NULL_CARD;
}
