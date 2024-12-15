#include <iostream>
#include <chrono>
#include <cstdlib>
#include "include/Game.h"

int main () {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(seed);
    
    Game game(100, 50);

    std::cout << "Initialization..." << std::endl;
    game.init(20);

    std::cout << "Saving..." << std::endl;
    game.saveState("file.txt");

    std::cout << "Loading..." << std::endl;
    game.loadState("file.txt");

    std::cout << "Initial state: " << std::endl;
    std::cout << game << std::endl;

    std::cout << std::endl << "===== FIGHT =====" << std::endl << std::endl;
    game.battle(10.0, 50.0, 5.0);

    std::cout << std::endl << "===== FIGHT END =====" << std::endl << std::endl;
    std::cout << "Survivors:" << std::endl;
    std::cout << game << std::endl;

    return 0;
}
