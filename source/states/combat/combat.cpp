#include "combat.h"
//đổi tên từ battle.cpp

void Game::display_combat()
{
    // int frameStart = SDL_GetTicks();
    if (combatStart)
    {
        init_components(deckObj, stageEnemies);
        cout << "Initiation success" << endl;
        combatStart = false;
    }
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &background);
    piles_process(dcpButton, drpButton, deckObj);
    ironclad.display();
    enemy_process(stageEnemies);
    if (stageEnemies.size() == 0) combat_win();
    // cout << SDL_GetTicks() - frameStart << endl; 
    if (turn%2 == 0)
    {
        if (rebuildHand) //for testing 
        {
            deckObj.discard_hand();
            if (deckObj.drawPile.size() == 0)
            {
                deckObj.drawPile = deckObj.discardPile;
                deckObj.discardPile.clear();
            }
            deckObj.build_hand();
            rebuildHand = false;
        }
        etButton.display();
        ironclad.display_energy();
        if (etButton.detect_click())
        {
            turn++;
        }
        hand_process(deckObj);
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        game.tick++;
        if (enemy_turn(ironclad, stageEnemies)) //wait for enemy_turn() to finish
        {
            game.tick = 0;
            ironclad.reset_energy();
            rebuildHand = true;
            turn++;
        }
    }
}
