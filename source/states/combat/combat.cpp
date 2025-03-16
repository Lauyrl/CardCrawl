#include "combat.h"
//đổi tên từ battle.cpp

void Game::display_combat()
{
    // int frameStart = SDL_GetTicks();
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &background);
    if (combatInit)
    {
        init_components(stageEnemies);
        combatInit = false;
    }
    ironclad.display();
    enemy_process(stageEnemies);
    if (stageEnemies.size() == 0) combat_win();
    
    if (turn%2 == 0)
    {
        if (charaRenew)
        {
            deck.renew_hand();
            ironclad.block = 0;
            charaRenew = false;
        }
        if (!inMenu && etButton.detect_click()) turn++;
        ironclad.display_energy();
        etButton.display();
        deck.hand_process(inMenu, stageEnemies);
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        if (enemy_turn(stageEnemies)) //wait for enemy_turn() to finish
        {
            ironclad.reset_energy();
            charaRenew = true;
            turn++;
        }
    }
    piles_process(dcpButton, drpButton);
    panel.display();
}
