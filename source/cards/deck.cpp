#include "deck.h" //using namespace std; included i think

size_t Deck::maxSize = 0; //size needs to be static and defined here or it breaks
// vector<Card> Deck::hand;
// vector<Card> Deck::drawPile;
// vector<Card> Deck::discardPile;

Deck::Deck(int maxSize_)
{
    maxSize = maxSize_;
}

void Deck::set_up_dp()
{
    shuffle_vector(ironclad.cardIdInventory);
    drawPile.resize(ironclad.cardIdInventory.size());
    for (size_t i{0}; i < ironclad.cardIdInventory.size(); i++)
    {
        Card card(ironclad.cardIdInventory[i], i);
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
        discardPile.push_back(hand[toDiscard]);
        hand.erase(hand.begin() + toDiscard);
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

void Deck::select_card(int toSelect)
{
    if (ironclad.energy >= hand[toSelect].attributes.cost && toSelect != selectedCardIdx)
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

void Deck::activate_card_process(vector<Enemy> &stageEnemies)
{
    int queried = NULL_TARGET;
    if (hand[selectedCardIdx].attributes.intent == Attack) 
         queried = hand[selectedCardIdx].query_targetE(stageEnemies);
    else queried = hand[selectedCardIdx].query_targetC();
    if (queried != NULL_TARGET)
    {
        cout << "Queried target: " << queried << endl;
        hand[selectedCardIdx].activate(stageEnemies, queried); //This passed the 0th enemy if the target is Character, can cause unintended behavior
        toDiscard = selectedCardIdx;
        selectedCardIdx = NULL_CARD;
    }
}

void Deck::interact_cards(int current, vector<Enemy> &stageEnemies)
{
    if (hand[current].detect_click()) 
    {
        select_card(current);
    }
    if (selectedCardIdx != NULL_CARD) //SlCI is NULL_CARD after activation adn by default
    {
        activate_card_process(stageEnemies);
    }
}

void Deck::renew_hand()
{
    discard_hand();
    if (drawPile.size() == 0)
    {
        drawPile = discardPile;
        discardPile.clear();
    }
    build_hand();
}

void Deck::show_pile(vector<Card>& pile, int textType)
{
    SDL_Rect greyOut = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(game.renderer, 20, 20, 20, 80);
    SDL_RenderFillRect(game.renderer, &greyOut);
    for (int i{0}; i < pile.size(); i++)
    {
        pile[i].display_copy(200+200*(i%5), 160+240*(int)(i/5));
    }
    if (textType == DC_TEXT) pileLabel.render_text("                                       DISCARD PILE\nOnce full, cards are pushed back into draw pile\nAll cards currently in hand are discarded upon turn end");
    if (textType == DP_TEXT) pileLabel.render_text("                                       DRAW PILE\nOnce empty, cards are retrieved from discard pile\nEach turn, by default, 5 cards are drawn from the draw pile into hand");

}
