#include "battle.h"

extern Game game; 
extern Character ironclad;
// void update_battle(Deck deckObj, )
// {

// }

void Game::display_battle()
{
    SDL_Rect background{0, 380, 1920, 1225};
    if (battleStart)
    {
        deckObj = deck_init(DECK_MAX_SIZE);
        deckObj.set_up(ironclad);
        test = enemy_init(acid_slime);
        cout << "Initiation success" << endl;
        battleStart = false;
    }

    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &background);
    test.enemy_display(test.attributes);
    if (test.detect_cursor_hover(cursorX, cursorY)) cout << "Hovering enemy" << endl;
    deckObj.toRemove = NULL_CARD;
    for (size_t i{0}; i < deckObj.size; i++)
    {
        deckObj.hand[i].object_loop(i, deckObj.selectedCardIndex, deckObj.toRemove, ironclad, test); 
    }
    if (deckObj.toRemove != NULL_CARD) {deckObj.remove_card(deckObj.toRemove);}
}
