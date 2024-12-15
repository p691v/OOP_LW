#include "../../include/NPCs/Werewolf.h"

Werewolf::Werewolf (Point<int> pos, std::string name) : NPC(pos, name, NPCType::WerewolfType, 40, 5, 'W') {}

bool Werewolf::fight (const Bandit &other) {
    fightNotify(other.getName());
    return true;
}

bool Werewolf::fight (const Orc &other) {
    return false;
}

bool Werewolf::fight (const Werewolf &other) {
    return false;
}

bool Werewolf::accept (std::shared_ptr<NPC> other) {
    return other->fight(*this);
}

void Werewolf::move (std::size_t mapWidth, std::size_t mapHeight) {
    std::lock_guard<std::shared_mutex> lock(mtx);

    for (std::size_t i = 0; i < getMovePoints(); i++) {
        Point<int> dPos(std::rand() % 3 - 1, std::rand() % 3 - 1);
        position = position + dPos;

        if (position.getX() < 0) position.setX(0); 
        else if (position.getX() >= mapWidth) position.setX(mapWidth - 1); 
        if (position.getY() < 0) position.setY(0); 
        else if (position.getY() >= mapHeight) position.setY(mapHeight - 1); 
    }
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