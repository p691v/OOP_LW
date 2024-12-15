#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <cstring>
#include "include/Game.h"

using namespace std::chrono_literals;

const std::size_t mapWidth = 50;
const std::size_t mapHeight = 30;
const std::size_t initialUnitsCount = 30;

int main (int argc, char **argv) {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(seed);

    bool printMurderLog = argc >= 2 && strcmp(argv[1], "--murders") == 0;
    
    Game game(mapWidth, mapHeight);

    std::cout << "Initialization..." << std::endl;
    game.init(initialUnitsCount);

    std::this_thread::sleep_for(300ms);

    std::cout << "Saving..." << std::endl;
    game.saveState("file.txt");

    std::this_thread::sleep_for(500ms);

    std::cout << "Loading..." << std::endl;
    game.loadState("file.txt");

    std::this_thread::sleep_for(500ms);

    std::cout << "Initial state: " << std::endl;
    std::cout << game << std::endl;

    std::this_thread::sleep_for(5s);

    std::cout << "===== READY? =====" << std::endl;
    std::this_thread::sleep_for(1500ms);

    for (std::size_t countdown = 3; countdown > 0; countdown--) {
        std::cout << "=== " << countdown << " ===" << std::endl;
        std::this_thread::sleep_for(1s);
    }

    std::cout << std::endl << "===== FIGHT =====" << std::endl << std::endl;
    std::this_thread::sleep_for(1s);
    game.battle(printMurderLog);

    std::cout << std::endl << "===== FIGHT END =====" << std::endl << std::endl;
    std::cout << "Survivors:" << std::endl;
    std::cout << game << std::endl;

    return 0;
}
