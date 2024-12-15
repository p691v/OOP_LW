#include "../../include/observers/ObserverStdout.h"

void ObserverStdout::notify (FightEvent event) {
    std::cout << event.attackerName;
    std::cout << " " << (event.attackerWin ? "win" : "lose");
    std::cout << " " << event.defenderName << std::endl;
}