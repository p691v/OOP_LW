#include "../../include/NPCs/Werewolf.h"

Werewolf::Werewolf (Point<int> pos, std::string name) : NPC(pos, name, NPCType::WerewolfType) {}

bool Werewolf::fight (const Bandit &other) {
    fightNotify(other.getName(), true);
    return true;
}

bool Werewolf::fight (const Orc &other) {
    fightNotify(other.getName(), false);
    return false;
}

bool Werewolf::fight (const Werewolf &other) {
    fightNotify(other.getName(), false);
    return false;
}

bool Werewolf::accept (std::shared_ptr<NPC> other) {
    return other->fight(*this);
}

std::ostream& Werewolf::print (std::ostream &os) {
    os << "Werewolf {" << std::endl;
    os << "\tname: " << getName() << std::endl;
    os << "\tposition: " << getPos() << std::endl;
    os << "}";

    return os;
}

std::ostream& operator<<(std::ostream &os, Werewolf &werewolf) {
    return werewolf.print(os);
}