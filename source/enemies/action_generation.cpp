#include "action_generation.h"

void reset_usage(vector<possibleActions>& actions)
{
    for (auto &action:actions) action.usage = 0;
}

Action rand_get(vector<possibleActions>& actions)
{
    while(true)
    {
        int value = rand_int(0, 100);
        for (size_t i{0}; i < actions.size(); i++)
        {
            if (value <= actions[i].value && actions[i].usage < actions[i].usageMax) 
            {
                if (actions[i].usage == 0) reset_usage(actions);
                actions[i].usage++;
                return actions[i].actionObj;
            }
        }
    }
}

Action rotate_get(vector<possibleActions>& actions)
{
    rotate(actions.begin(), actions.begin()+1, actions.end());
    return actions.back().actionObj;
}
