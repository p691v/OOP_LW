#include "../../include/observers/ObserverStdout.h"

void ObserverStdout::notify (FightEvent event) {
    Printer() << event.attackerName << " attack " << event.defenderName << "\n";
}