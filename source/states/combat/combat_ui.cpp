#include "combat_ui.h"

EndTurnButton::EndTurnButton() : Gui(900, 600, 130, 40) {}

void EndTurnButton::display()
{
    SDL_SetRenderDrawColor(game.renderer, 0, 60, 120, 100);
    SDL_RenderFillRect(game.renderer, &rect);
    etText.render_text("End Turn");
}

// DRAW
bool DrawPileButton::displaying = false;
DrawPileButton::DrawPileButton() : Gui(10, 670, 150, 150) {}
void DrawPileButton::display()
{
    game.render_img("assets/ui/combat/draw_pile.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

void DrawPileButton::button_process()
{
    static vector<Card> copy;
    if (detect_click())
    {
        copy = deck.drawPile; shuffle_vector(copy);
        if (!displaying) displaying = true;
        else displaying = false;
        panel.dButton.active = false;
    }
    if (displaying) deck.display_pile(copy, DP_TEXT);
    display();

}

// DISCARD
bool DiscardPileButton::displaying = false;
DiscardPileButton::DiscardPileButton() : Gui(1340, 670, 150, 150) {}
void DiscardPileButton::display()
{
    game.render_img("assets/ui/combat/discard_pile.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

void DiscardPileButton::button_process()
{
    if (detect_click())
    {
        if (!displaying) displaying = true;
        else displaying = false;
        panel.dButton.active = false;
    }
    if (displaying) deck.display_pile(deck.discardPile, DC_TEXT);
    display();
}
