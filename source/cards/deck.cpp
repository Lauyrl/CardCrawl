#include "deck.h" //using namespace std; included i think

size_t Deck::maxSize = 0; //size needs to be static and defined here or it breaks
Deck::Deck(int maxSize_) {maxSize = maxSize_;}

void Deck::set_up_piles(bool shuffle)
{
    renew();
    vector<cardIdInv> copy = ironclad.cardIdInv;
    if (shuffle) shuffle_vector(copy);
    drawPile.resize(copy.size());
    for (size_t i{0}; i < copy.size(); i++)
    {
        Card card(copy[i], i);
        add_card(drawPile, i, card);
        cout << "Added card " << i << " to draw pile" << endl;
    }
}

void Deck::add_card(vector<Card> &pile, int idx, Card card)
{
    pile[idx] = card;
    pile[idx].pos = idx;
    pile[idx].move_rect(CARD_POS_X_DEFAULT+STEP_INCREMENT*pile[idx].pos, CARD_POS_Y);
    // cout << "Added card " << idx << " to pile" << endl;
}

void Deck::display_pile(vector<Card>& pile, int textType, bool move)
{
    SDL_Rect greyOut = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(game.renderer, 8, 8, 8, 80);
    SDL_RenderFillRect(game.renderer, &greyOut);
    for (int i{0}; i < pile.size(); i++)
    {
        pile[i].display_copy(252+200*(i%5), 150+260*(int)(i/5), move);
    }
    if (textType == DC_TEXT) pileLabel.render_text("                                       DISCARD PILE\nOnce full, cards are pushed back into draw pile\nAll cards currently in hand are discarded upon turn end");
    if (textType == DP_TEXT) pileLabel.render_text("                                       DRAW PILE\nOnce empty, cards are retrieved from discard pile\nEach turn, by default, 5 cards are drawn from the draw pile into hand");
}

int Deck::interact_cards_event()
{
    for (int i{0}; i < drawPile.size(); i++) 
        if (drawPile[i].detect_click()) return i;
    return NULL_CARD;
}

void Deck::renew()
{
    drawPile.clear(); hand.clear(); discardPile.clear();
    selectedIdx = NULL_CARD; usedIdx = NULL_CARD;
}
