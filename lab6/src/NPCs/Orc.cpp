#include "../../include/NPCs/Orc.h"

Orc::Orc (Point<int> pos, std::string name) : NPC(pos, name, NPCType::OrcType) {}

bool Orc::fight (const Bandit &other) {
    fightNotify(other.getName(), true);
    return true;
}

bool Orc::fight (const Orc &other) {
    fightNotify(other.getName(), false);
    return false;
}

bool Orc::fight (const Werewolf &other) {
    fightNotify(other.getName(), false);
    return false;
}

bool Orc::accept (std::shared_ptr<NPC> other) {
    return other->fight(*this);
}

std::ostream& Orc::print (std::ostream &os) {
    os << "Orc {" << std::endl;
    os << "\tname: " << getName() << std::endl;
    os << "\tposition: " << getPos() << std::endl;
    os << "}";

    return os;
}

std::ostream& operator<<(std::ostream &os, Orc &orc) {
    return orc.print(os);
}
