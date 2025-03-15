#pragma once

#include <set>
#include <cstring>
#include "../../gui/top_panel.h"

class Node : public Gui
{
    public:
        Node();
        Node(int pos_, int lev_);
        bool select();
        void rand_type();
        int pos;
        int lev;
        int id;
        enum nodeType {
            combat, shop, event, rest
        };
        static vector<nodeType> possibleTypes;
        nodeType type;
        bool crossed{false};
        set<int> prev;
        set<int> next; 
};

class Tree
{
    public:
        Tree();
        void generate_path(int start);
        void nodes_process();
        void display();
        Node& cache_node(int pos, int lev);
        static vector<int> playerPath;
        static map<int, Node> nodeMap;
        static int playerCurrentLev;
};

