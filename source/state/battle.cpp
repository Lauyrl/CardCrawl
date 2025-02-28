#include "battle.h"

extern Game game; 
extern Character ironclad;

void init_components(Deck &deckObj, vector<Enemy> &stage_enemies)
{
    etButton = et_button_init();
    eu = eu_init();
    turn = 0;
    deckObj = deck_init(DECK_MAX_SIZE);
    deckObj.set_up(ironclad);
    for (size_t i{0}; i < MAX_ENEMIES; i++)
    {
        stage_enemies[i] = enemy_init(acid_slime, i);
    }
}

void deck_process(Deck &deckObj)
{
    deckObj.toRemove = NULL_CARD;
    for (size_t current{0}; current < deckObj.size; current++)
    {
        deckObj.deck_iterate(current, ironclad, stage_enemies); 
    }
    if (deckObj.toRemove != NULL_CARD) deckObj.remove_card();
}

void enemies_process(vector<Enemy> &stage_enemies)
{
    for (int i{stage_enemies.size()-1}; i >= 0 ; i--)
    {
        if (stage_enemies[i].attributes.hp <= 0) stage_enemies.erase(stage_enemies.begin()+i);
        stage_enemies[i].enemy_display();
    }
}

void Game::display_battle()
{
    if (battleStart)
    {
        init_components(deckObj, stage_enemies);
        cout << "Initiation success" << endl;
        battleStart = false;
    }
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &background);

    ironclad.character_display();

    enemies_process(stage_enemies);
    
    if (turn%2 == 0)
    {
        etButton.et_button_display();
        eu.energy_display();
        if (etButton.detect_click())
        {
            turn++;
        }
        deck_process(deckObj);
    }
    else
    {
        for (size_t i{0}; i < stage_enemies.size(); i++)
        {
            stage_enemies[i].eAction(ironclad);
        }
        turn++;
    }
}
