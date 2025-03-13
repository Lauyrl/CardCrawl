#include "event.h"

void duplicator_pray_ef()
{
    cout << "test" << endl;
}
void leave_ef()
{
    cout << "tesssssssssst" << endl;
    game.state_switch(Game::gameStates::map);
}
const map<choiceId, choiceAttributes> Choice::choiceAttriMap = {
    {duplicator_pray, {"test", duplicator_pray_ef}},
    {leave,           {"leave", leave_ef}}
};


static vector<Choice> duplicatorVector = {
    Choice(duplicator_pray, 0), Choice(leave, 1)
};

const map<eventId, eventAttributes> Event::evMap = {
    {duplicator ,{"assets/ui/event/e_duplicator.png", "duplicator", "Test test teset", duplicatorVector}}
};
