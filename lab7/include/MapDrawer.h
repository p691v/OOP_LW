#pragma once
#include <vector>
#include <set>
#include <memory>
#include "Printer.h"
#include "NPC.h"

class MapDrawer {
    private: 
        std::size_t mapWidth;
        std::size_t mapHeight;

    public:
        MapDrawer (std::size_t width, std::size_t height);

        void operator() (std::set<std::shared_ptr<NPC>> &npcs);
};