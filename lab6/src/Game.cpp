#include "../include/Game.h"

Game::Game (std::size_t width, std::size_t height) : mapWidth{width}, mapHeight{height} {
    screenOut = std::make_shared<ObserverStdout>();
    fileOut = std::make_shared<ObserverFile>("log.txt");
}

void Game::init (std::size_t unitsCount) {
    units.clear();

    FactoryRandom factory(mapWidth, mapHeight);

    for (int i = 0; i < unitsCount; i++) {
        auto npc = factory.CreateRandomNPC();
        npc->subscribe(screenOut);
        npc->subscribe(fileOut);
        units.insert(npc);
    }
}

void Game::saveState (std::string filename) {
    FactoryFile::NPCSaver saver(filename, units.size());

    for (const auto &npc : units) {
        saver.saveNPC(npc);
    }
}

void Game::loadState (std::string filename) {
    units.clear();

    FactoryFile factory(filename);

    while (!factory.fileEnd()) {
        auto npc = factory.CreateNPCFromFile();
        npc->subscribe(screenOut);
        npc->subscribe(fileOut);
        units.insert(npc);
    }
}

Game::NPCSet Game::battle_step (double killDistance) {
    NPCSet killed;
    
    for (const auto &attacker : units) {
        for (const auto &defender : units) {
            if (attacker == defender || !attacker->isClose(defender, killDistance)) continue;
            
            if (defender->accept(attacker)) {
                killed.insert(defender);
            }
        }
    }

    return killed;
}

void Game::battle (double distanceBegin, double distanceEnd, double distanceStep) {
    for (double killDistance = distanceBegin; killDistance < distanceEnd; killDistance += distanceStep) {
        std::cout << "===== FIGHT CYCLE =====" << std::endl;
        std::cout << "Kill distance: " << killDistance << std::endl << std::endl;

        auto killed = battle_step(killDistance);

        std::cout << std::endl << "Murdered: " << std::endl;
        
        for (auto &npc : killed) {
            units.erase(npc);
            std::cout << *npc << std::endl;
        }

        std::cout << std::endl << "===== FIGHT CYCLE END =====" << std::endl;

        std::cout << std::endl;
    }
}

std::ostream& operator<< (std::ostream &os, Game &game) {
    for (const auto &npc : game.units) {
        os << *npc << std::endl;
    }

    return os;
}