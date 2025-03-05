#include "battle.h"

extern Game game; 
extern Character ironclad;

void init_components(Deck &deckObj, vector<Enemy> &stageEnemies)
{
    turn = 0;
    deckObj.set_up_draw_pile(ironclad);
    deckObj.build_hand();
    for (int i{0}; i < MAX_ENEMIES; i++)
    {
        stageEnemies.push_back(Enemy(acid_slime, i));
    }
}

void deck_process(Deck &deckObj)
{
    deckObj.toDiscard = NULL_CARD;
    for (size_t current{0}; current < deckObj.hand.size(); current++)
    {
        deckObj.interact_cards(current, ironclad, stageEnemies); 
    }
    if (deckObj.toDiscard != NULL_CARD) 
    {
        deckObj.discardPile.push_back(deckObj.hand[deckObj.toDiscard]);
        deckObj.discard_card();
    }
}

void enemy_process(vector<Enemy> &stageEnemies)
{
    for (int i{stageEnemies.size()-1}; i >= 0 ; i--)
    {
        if (stageEnemies[i].attributes.hp <= 0) stageEnemies.erase(stageEnemies.begin()+i);
        else stageEnemies[i].display();
    }
}

bool enemy_turn(Character &chara, vector<Enemy> &stageEnemies)
{
    // bool progress = false;
    // progress = ; 
    if (!stageEnemies[activeEnemyIdx].enemy_action(ironclad)) return false; // return true after animation finishes
    else 
    {
        game.tick = 0;
        activeEnemyIdx++;
        if (activeEnemyIdx < stageEnemies.size()) return false;
    }
    activeEnemyIdx = 0;
    return true;
}

void Game::display_battle()
{
    // int frameStart = SDL_GetTicks();
    if (battleStart)
    {
        init_components(deckObj, stageEnemies);
        cout << "Initiation success" << endl;
        battleStart = false;
    }
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &background);
    drpButton.display();
    dcpButton.display();
    //
    if (drpButton.detect_click()) 
    {
        for (size_t i{0}; i < deckObj.drawPile.size(); i++)
        {
            cout << deckObj.drawPile[i].id << ' ';
        }
        cout << endl;
    }

    if (dcpButton.detect_click()) 
    {
        for (size_t i{0}; i < deckObj.discardPile.size(); i++)
        {
            cout << deckObj.discardPile[i].id << ' ';
        }
        cout << endl;
    }

    ironclad.display();
    enemy_process(stageEnemies);
    // cout << SDL_GetTicks() - frameStart << endl; 
    if (turn%2 == 0)
    {
        if (playerTurn) //this is for testing only pls change
        {
            deckObj.clear_hand();
            if (deckObj.drawPile.size() == 0)
            {
                deckObj.drawPile = deckObj.discardPile;
                deckObj.discardPile.clear();
            }
            deckObj.build_hand();
            playerTurn = false;
        }
        etButton.display();
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
        game.tick++;
        if (enemy_turn(ironclad, stageEnemies)) //wait for enemy_turn() to finish
        {
            game.tick = 0;
            ironclad.reset_energy();
            turn++;
            playerTurn = true;
        }
    }
}
