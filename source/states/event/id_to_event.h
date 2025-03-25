#pragma once

#include <vector>
#include <functional>

using namespace std;
enum eventId {
    duplicator, bf_spirits, gshrine, cleric
};
class Choice;
struct eventAttributes
{
    string imgName;
    string titleText;
    string descText;
    vector<Choice> choices;
    bool unique;
};


enum choiceId {
    leave,
    duplicator_pray,
    bf_spirits_offer,
    gshrine_pray,
    cleric_heal, cleric_purify
};
struct choiceAttributes
{
    int uses;
    string label;
    function<bool()> effect;
};
