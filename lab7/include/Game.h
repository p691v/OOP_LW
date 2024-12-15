#pragma once
#include <set>
#include <thread>
#include "NPC.h"
#include "NPCs/Bandit.h"
#include "NPCs/Orc.h"
#include "NPCs/Werewolf.h"
#include "factories/FactoryRandom.h"
#include "factories/FactoryFile.h"
#include "observers/ObserverStdout.h"
#include "observers/ObserverMurderStdout.h"
#include "observers/ObserverFile.h"
#include "FightManager.h"
#include "MoveManager.h"
#include "MapDrawer.h"

class Game {
    private:
        using NPCSet = std::set<std::shared_ptr<NPC>>;

        std::size_t mapWidth;
        std::size_t mapHeight;
        NPCSet units;

        std::shared_ptr<ObserverStdout> screenOut{nullptr};
        std::shared_ptr<ObserverMurderStdout> screenMurderOut{nullptr};
        std::shared_ptr<ObserverFile> fileOut{nullptr};

    public:
        Game (std::size_t width, std::size_t height);

        void init (std::size_t unitsCount);
        void saveState (std::string filename);
        void loadState (std::string filename);

        void battle (bool printMurderLog);

        friend std::ostream& operator<<(std::ostream &os, Game &game);
};