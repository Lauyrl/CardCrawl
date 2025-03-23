#include "map_elements.h"
// doi ten tu "map_elements.cpp"
Node::Node() : Gui(0, 0, 60, 60) {}

Node::Node(int pos_, int lev_) : Gui(0, 0, 60, 60)
{
    pos = pos_;
    lev = lev_;
    id  = lev*10+pos;
    type = combat;
    move_rect(270+150*pos, NODE_POS_Y_DEFAULT+NODE_Y_STEP_INCREMENT*lev);
}

vector<Node::nodeType> Node::possibleTypes = {combat, combat, combat, rest, event, event, treasure, shop}; //combat, rest, event, shop, treasure
void Node::rand_type()
{
    shuffle_vector(possibleTypes);
    type = possibleTypes.back();
}

bool Node::select()
{
    if (detect_click()) 
    {
        switch (type)
        {
            case (combat):
            {
                game.state_switch(game.gameStates::combat);
                game.combatInit = true;
                return true;
            }
            case (rest):
            {
                game.state_switch(game.gameStates::rest);
                game.restInit = true;
                return true;
            }
            case (event):
            {
                game.state_switch(game.gameStates::event);
                game.eventInit = true;
                return true;
            }
            case (shop):
            {
                game.state_switch(game.gameStates::shop);
                game.shopInit = true;
                return true;
            }
            case (treasure):
            {
                game.state_switch(game.gameStates::treasure);
                game.treasureInit = true;
                return true;
            }
        }
    }
    return false;
}
