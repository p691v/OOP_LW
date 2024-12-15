#include "../../include/observers/ObserverMurderStdout.h"

void ObserverMurderStdout::notify (MurderEvent event) {
    Printer() << event.killerName << " kill " << event.victimName << "\n";
}