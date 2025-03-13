#include "map.h"

void Game::display_map()
{
    if (!mapGenerated)
    {
        // for (auto node:tree.nodeMap)
        // {
        //     cout << "p(";
        //     for (auto previous:node.second.prev) cout << previous << " ";
        //     cout << ") : " << "(" << node.second.pos << ", " << node.second.lev << ")" << " : n(";
        //     for (auto nxt:node.second.next) cout << nxt << " ";
        //     cout << ")" << endl;
        // }
        mapGenerated = true;
    }
    render_img("assets/map/map_mid.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255, NULL);
    tree.nodes_process();

    panel.display();
}


