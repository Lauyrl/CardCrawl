#include "battle.h"

extern Game game; 
extern Character ironclad;

void Game::display_battle()
{
    if (battleStart)
    {
        deckObj = deck_init(DECK_MAX_SIZE);
        deckObj.set_up(ironclad);
        for (size_t i{0}; i < MAX_ENEMIES; i++)
        {
            stage_enemies[i] = enemy_init(acid_slime, i);
        }
        cout << "Initiation success" << endl;
        battleStart = false;
    }
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &background);

    for (int i{numOfEnemies-1}; i >= 0 ; i--)
    {
        if (stage_enemies[i].attributes.hp <= 0) stage_enemies.erase(stage_enemies.begin()+i);
        stage_enemies[i].enemy_display(stage_enemies[i].ePos);
    }
    numOfEnemies = stage_enemies.size();
    
    deckObj.toRemove = NULL_CARD;
    for (size_t i{0}; i < deckObj.size; i++)
    {
        deckObj.hand[i].card_display(deckObj.hand[i].id, deckObj.hand[i].pos);
        deckObj.deck_iterate(i, ironclad, stage_enemies, numOfEnemies); 
    }
    if (deckObj.toRemove != NULL_CARD) deckObj.remove_card();
}
