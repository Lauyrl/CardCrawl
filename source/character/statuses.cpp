#include "character.h"

map<statusId, Status> Character::statuses = globalStatuses;

void Character::decrement_statuses()
{
    for (auto& status:statuses)
    {
        if (decrementableStatuses.find(status.first) != decrementableStatuses.end() && status.second.level > 0)
            status.second.level--;
    }
    if (flexCnt)
    {
        statuses[strength].level -= 2*flexCnt;
        flexCnt = 0;
    }
    cout << "strength: " << statuses[strength].level << endl;
}

void Character::cleanse()
{
    for (auto& status:statuses)
    {
        if (debuffs.find(status.first) != debuffs.end() && status.second.level > 0)
            status.second.level = 0;
    } 
}

void Status::display()
{
    game.render_img(sprite, rect.x, rect.y, rect.w, rect.h, 200, NULL);
    levelText = Text(16, rect.x+26, rect.y+16, 240, 240, 240);
    levelText.render_text(to_string(level));
    if (detect_cursor_hover()) display_desc();
}
void Status::display_desc()
{
    game.render_img("assets/ui/popup.png", rect.x-198, rect.y-15, 700, 150, 220, NULL);
    descText = Text(20,rect.x, rect.y+35, 220, 220, 220);
    descText.render_text(desc+to_string(level));
}
