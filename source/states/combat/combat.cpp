#include "combat.h"
//đổi tên từ battle.cpp

void Game::display_combat()
{
    // int frameStart = SDL_GetTicks();
    game.render_img("assets/scene/scene.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, &background);
    if (combatInit)
    {
        init_components();
        combatInit = false;
    }
    ironclad.display();
    enemy_process();
    if (death()) return;
    if (stageEnemies.size() == 0) 
    {
        combat_win();
        return;
    }
    if (turn%2 == 0)
    {
        if (charaTurnRenew)
        {
            deck.renew_hand();
            ironclad.renew_turn();
            enemy_generate_intents();
            charaTurnRenew = false;
        }
        if (!inMenu && et.detect_click()) 
        { 
            turn++; 
            ironclad.decrement_statuses(); 
            for (auto& enemy:stageEnemies) enemy.block = 0;
        }
        et.display();
        ironclad.display_energy();
        deck.hand_process(inMenu, stageEnemies);
        ironclad.during_turn_relic();
        //cout << SDL_GetTicks() - frameStart << endl; 
    }
    else
    {
        if (enemy_turn()) //wait for enemy_turn() to finish
        {
            for (auto& enemy:stageEnemies) enemy.decrement_statuses();
            charaTurnRenew = true;
            turn++;
        }
    }
    piles_process();
    panel.display();
}


EndTurnButton et;
DrawPileButton drp;
DiscardPileButton dcp;
vector<vector<enemyId>> formations = {
    //{acid_slime, acid_slime, acid_slime, acid_slime},
    //{cultist, cultist},
    //{slaver_blue, slaver_blue},
    {champ},
};
vector<Enemy> stageEnemies;
RewardMenu rMenu;
int turn = 0;
int activeEnemyIdx = 0;
bool inMenu = false;
bool charaTurnRenew = false;

void enemy_generate()
{
    stageEnemies.clear();
    shuffle_vector(formations);
    vector<enemyId> chosen = formations.front();
    int x{ENEMY_POS_X};
    for (int i{0}; i < chosen.size(); i++) 
    {   
        stageEnemies.push_back(Enemy(chosen[i], i, x));
        stageEnemies.back().generate_intent(0);
        x += 235+50*stageEnemies.back().attributes.size;
    }
}

void init_components()
{
    turn = 0;
    deck.set_up_piles();
    deck.build_hand();
    ironclad.renew();
    enemy_generate();
    rMenu.generate_items(20, 100, 6, 10, 9, 7, 10, 9);
    cout << "Initiation success" << endl;
}

void piles_process()
{
    if (!panel.inMenu)
    {
        if (!drp.displaying) dcp.button_process();
        if (!dcp.displaying) drp.button_process();
    }
    else { drp.displaying = false; dcp.displaying = false; }
    inMenu = (drp.displaying || dcp.displaying || panel.inMenu);
}

void enemy_process()
{
    for (int i{stageEnemies.size()-1}; i >= 0 ; i--)
    {
        if (stageEnemies[i].attributes.hp <= 0) 
        {
            stageEnemies.erase(stageEnemies.begin()+i);
            if (ironclad.check_relic(gremlin_horn)) ironclad.relicInv.at(gremlin_horn).attributes.effect(); 
        }
        else stageEnemies[i].display();
    }
}

void enemy_generate_intents() { for (auto& enemy:stageEnemies) enemy.generate_intent(turn); }

bool enemy_turn()
{
    if (!stageEnemies[activeEnemyIdx].enemy_action()) return false; // return true after animation finishes
    else 
    {
        activeEnemyIdx++;
        if (activeEnemyIdx < stageEnemies.size()) return false;
    }
    activeEnemyIdx = 0;
    return true;
}

void combat_win()
{
    if (rMenu.process())
    {
        stageEnemies.clear();
        game.state_switch(game.gameStates::map);
    }
    panel.display();
}

bool death()
{   
    static int t{0};
    if (ironclad.health <= 0)
    {
        t++;
        if (t < 60)
        {
            SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255/60*t);
            SDL_RenderFillRect(game.renderer, &black);
        }
        else if (t == 80)
        {
            t = 0;
            turn = 0; activeEnemyIdx = 0;
            inMenu = false; charaTurnRenew = false;
            stageEnemies.clear();
            game.combatInit = true;
            game.mapGenerated = false;
            game.state_switch(Game::gameStates::start_menu);
        }
        else
        {
            SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(game.renderer, &black);
        }
        return true;
    }
    else return false;
}
