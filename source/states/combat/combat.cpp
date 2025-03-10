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
    ironclad.display();
    enemy_process(stageEnemies);
    if (stageEnemies.size() == 0) combat_win();
    if (turn%2 == 0)
    {
        if (rebuildHand) //for testing 
        {
            deckObj.renew_hand();
            rebuildHand = false;
        }
        ironclad.display_energy();
        etButton.display();
        if (!inMenu && etButton.detect_click()) turn++;
        hand_process(deckObj);
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        if (enemy_turn(ironclad, stageEnemies)) //wait for enemy_turn() to finish
        {
            ironclad.reset_energy();
            rebuildHand = true;
            turn++;
        }
    }
    piles_process(dcpButton, drpButton, deckObj);
}
