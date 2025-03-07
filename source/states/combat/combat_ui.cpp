#include "combat_ui.h"

extern Game game;

EndTurnButton::EndTurnButton() : Gui(900, 100, 130, 40) {}

void EndTurnButton::display()
{
    SDL_SetRenderDrawColor(game.renderer, 0, 60, 120, 100);
    SDL_RenderFillRect(game.renderer, &rect);
    etText.render_text("End Turn");
}

DrawPileButton::DrawPileButton() : Gui(10, 670, 150, 150) {}
void DrawPileButton::display()
{
    game.render_img("assets/ui/draw_pile.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}

DiscardPileButton::DiscardPileButton() : Gui(1340, 670, 150, 150) {}
void DiscardPileButton::display()
{
    game.render_img("assets/ui/discard_pile.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
}
