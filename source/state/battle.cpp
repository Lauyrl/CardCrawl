#include "battle.h"

extern Game game; 
extern Character ironclad;
void Game::display_battle()
{
    SDL_Rect background[1];
    background[0] = SDL_Rect{0, 380, 1920, 1225};
    game.render_img("assets/scene/scene.jpg",0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT, &background[0]);
    Deck deckObj = deck_init();
    Enemy test = enemy_init(acid_slime);
    if (battleInitiate)
    {
        deckObj.size = DECK_MAX_SIZE;
        deckObj.set_up(ironclad);
        cout << "Initiation success" << endl;
        battleInitiate = false;
    }

    test.enemy_display();
    if (test.detect_cursor_hover(cursorX, cursorY)) cout << "Hovering enemy" << endl;
    deckObj.toRemove = NULL_CARD;
    for (size_t i{0}; i < deckObj.size; i++)
    {
        deckObj.hand[i].object_loop(i, deckObj.selectedCardIndex, deckObj.toRemove, ironclad, test); 
    }
    if (deckObj.toRemove != NULL_CARD) {deckObj.remove_card(deckObj.toRemove);}
}
