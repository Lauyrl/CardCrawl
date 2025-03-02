#include "battle.h"

extern Game game; 
extern Character ironclad;

void init_components(Deck &deckObj, vector<Enemy> &stage_enemies)
{
    turn = 0;
    deckObj = Deck(DECK_MAX_SIZE);
    deckObj.set_up(ironclad);
    for (int i{0}; i < MAX_ENEMIES; i++)
    {
        stage_enemies.push_back(Enemy(acid_slime, i));
    }
}

void deck_process(Deck &deckObj)
{
    deckObj.toDiscard = NULL_CARD;
    for (size_t current{0}; current < deckObj.size; current++)
    {
        deckObj.deck_iterate(current, ironclad, stage_enemies); 
    }
    if (deckObj.toDiscard != NULL_CARD) deckObj.remove_card();
}

void enemies_process(vector<Enemy> &stage_enemies)
{
    for (int i{stage_enemies.size()-1}; i >= 0 ; i--)
    {
        if (stage_enemies[i].attributes.hp <= 0) stage_enemies.erase(stage_enemies.begin()+i);
        else stage_enemies[i].enemy_display();
    }
}

bool enemy_turn(Character &chara, vector<Enemy> &stage_enemies)
{
    // bool progress = false;
    // progress = ; 
    if (!stage_enemies[activeEnemyIndex].e_action(ironclad)) return false; // return true after animation finishes
    else 
    {
        game.timeDelta = 0;
        activeEnemyIndex++;
        if (activeEnemyIndex < stage_enemies.size()) return false;
    }
    activeEnemyIndex = 0;
    return true;
}

void Game::display_battle()
{
    // int frameStart = SDL_GetTicks();
    if (battleStart)
    {
        init_components(deckObj, stage_enemies);
        cout << "Initiation success" << endl;
        battleStart = false;
    }
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &background); 
    ironclad.character_display();
    enemies_process(stage_enemies);
    // cout << SDL_GetTicks() - frameStart << endl; 
    if (turn%2 == 0)
    {
        etButton.et_button_display();
        ironclad.display_energy();
        if (etButton.detect_click())
        {
            turn++;
        }
        deck_process(deckObj);
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        game.timeDelta++;
        if (enemy_turn(ironclad, stage_enemies)) //wait for enemy_turn() to finish
        {
            game.timeDelta = 0;
            ironclad.lose_energy(ironclad.energy-3); // Reset energy
            turn++;
        }
    }
}
