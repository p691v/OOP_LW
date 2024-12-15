#include "../../include/observers/ObserverFile.h"

void ObserverFile::notify (FightEvent event) {
    file << event.attackerName;
    file << " " << "attack";
    file << " " << event.defenderName << std::endl;
}

ObserverFile::ObserverFile (std::string filename) {
    file.open(filename);
    if (!file.is_open()) throw std::ios_base::failure("Failed to open file.");
}

ObserverFile::~ObserverFile () {
    if (file.is_open()) file.close();
}
