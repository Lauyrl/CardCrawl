#pragma once

#include <vector>
#include <functional>

using namespace std;
enum eventId {
    duplicator, bf_spirits 
};
class Choice;
struct eventAttributes
{
    string imgName;
    string titleText;
    string descText;
    vector<Choice> choices;
};


enum choiceId {
    leave,
    duplicator_pray
};
struct choiceAttributes
{
    int uses;
    string label;
    function<bool()> effect;
};
