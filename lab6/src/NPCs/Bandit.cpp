#include "../../include/NPCs/Bandit.h"

Bandit::Bandit (Point<int> pos, std::string name) : NPC(pos, name, NPCType::BanditType) {}

bool Bandit::fight (const Bandit &other) {
    fightNotify(other.getName(), false);
    return false;
}

bool Bandit::fight (const Orc &other) {
    fightNotify(other.getName(), false);
    return false;
}

bool Bandit::fight (const Werewolf &other) {
    fightNotify(other.getName(), true);
    return true;
}

bool Bandit::accept (std::shared_ptr<NPC> other) {
    return other->fight(*this);
}

std::ostream& Bandit::print (std::ostream &os) {
    os << "Bandit {" << std::endl;
    os << "\tname: " << getName() << std::endl;
    os << "\tposition: " << getPos() << std::endl;
    os << "}";

    return os;
}

std::ostream& operator<<(std::ostream &os, Bandit &bandit) {
    return bandit.print(os);
}