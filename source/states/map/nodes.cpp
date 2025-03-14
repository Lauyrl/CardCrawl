#include "map_elements.h"
// doi ten tu "map_elements.cpp"
Node::Node() : Gui(0, 0, 60, 60) {}

Node::Node(int pos_, int lev_) : Gui(0, 0, 60, 60)
{
    pos = pos_;
    lev = lev_;
    id = 10*pos_+lev_;
    type = combat;
    move_rect(270+150*pos, 750-80*lev);
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
                return true;
            }
            case (shop):
            {
                game.state_switch(game.gameStates::shop);
                return true;
            }
        }
        
    }
    return false;
}

vector<Node::nodeType> Node::possibleTypes = {event, shop}; //combat, rest, 
void Node::rand_type()
{
    shuffle_vector(possibleTypes);
    type = possibleTypes.back();
}
