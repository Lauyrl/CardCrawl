#include "event.h"

void Game::display_event()
{
    // srand(time(NULL));
    // int value = rand() % 100;
    // for (size_t i{0}; i < possibilities.size(); i++)
    // {
    //     if (value <= possibilities[i].actionValue) 
    //     {
    //         possibilities[i].action(*this);
    //         return false;
    //     }
    // }
    Event test;
    render_img("assets/scene/def_background.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    render_img("assets/events/panel.png", 50, 150, 1380, 650, 255, NULL);
    test.process();
    

    panel.display();
}

static vector<eventId> eventIdList = {duplicator};
Event::Event()
{
    shuffle_vector(eventIdList);
    id = eventIdList.back();
    attributes = evMap.at(id);
}

void Event::process()
{
    game.render_img(attributes.imgName.c_str(), 100, 260, 480, 480, 255, NULL);
    title.render_text(attributes.titleText);
    desc.render_text(attributes.descText);
    for (auto choice:attributes.choices) choice.process();
}


Choice::Choice(choiceId id_, int pos_) : Gui(580, 500+100*pos_, 800, 50) 
{
    id = id_;
    pos = pos_;
    attributes = choiceAttriMap.at(id);
}

void Choice::display()
{
    game.render_img("assets/ui/event/enabled_button.png", rect.x, rect.y, rect.w, rect.h, 255, NULL);
    label.render_text(attributes.label);
}

void Choice::process()
{
    display();
    if (detect_click()) attributes.effect();
}
