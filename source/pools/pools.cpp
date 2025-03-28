#include "pools.h"

const vector<cardId> commonCardPoolOrigin   = {strike, defend, iron_wave, flex, cleave, sword_boomerang, anger};
const vector<cardId> uncommonCardPoolOrigin = {bloodletting, intimidate, rage, intimidate, dropkick};
const vector<cardId> rareCardPoolOrigin     = {bludgeon};
 
const set<relicId> commonRelicPoolOrigin   = {anchor, blood_vial, bronze_scales, tea_set};
const set<relicId> uncommonRelicPoolOrigin = {shuriken, gremlin_horn, singing_bowl};
const set<relicId> rareRelicPoolOrigin     = {fossil_helix};

vector<cardId> commonCardPool   = commonCardPoolOrigin;
vector<cardId> uncommonCardPool = uncommonCardPoolOrigin;
vector<cardId> rareCardPool     = rareCardPoolOrigin;
 
set<relicId> commonRelicPool   = commonRelicPoolOrigin;
set<relicId> uncommonRelicPool = uncommonRelicPoolOrigin;
set<relicId> rareRelicPool     = rareRelicPoolOrigin;
