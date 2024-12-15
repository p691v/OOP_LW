#include "../../include/NPCs/Bandit.h"

Bandit::Bandit (Point<int> pos, std::string name) : NPC(pos, name, NPCType::BanditType, 10, 10, 'B') {}

bool Bandit::fight (const Bandit &other) {
    return false;
}

bool Bandit::fight (const Orc &other) {
    return false;
}

bool Bandit::fight (const Werewolf &other) {
    fightNotify(other.getName());
    return true;
}

bool Bandit::accept (std::shared_ptr<NPC> other) {
    return other->fight(*this);
}

void Bandit::move (std::size_t mapWidth, std::size_t mapHeight) {
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