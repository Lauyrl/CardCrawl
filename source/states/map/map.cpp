#include "map.h"

void Game::display_map()
{
    static Tree tree;
    if (!mapGenerated)
    {
        tree.renew();
        cout << "Tree generated" << endl;
        mapGenerated = true;
    }
    render_img("assets/map/map_mid.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    tree.nodes_process();

    panel.display();
}


