#include <stdexcept>
#include "../include/NPC.h"

std::set<std::string> NPC::usedNames;
std::size_t NPC::createdCount = 0;

void NPC::fightNotify (std::string defenderName) {
    notifySubs(FightEvent(getName(), defenderName));
}

NPC::NPC (Point<int> pos, std::string npcName, NPCType npcType, std::size_t move, std::size_t kill, char npcSprite) {
    name = "";

    if (usedNames.contains(npcName)) {
        throw std::logic_error(std::string("NPC with name ") + npcName + " already exists.");
    }

    usedNames.insert(npcName);

    position = pos;
    name = npcName;
    type = npcType;
    sprite = npcSprite;
    movePoints = move;
    killDistance = kill;

    alive = true;
    
    createdCount++;
}

NPC::~NPC () {
    if (name != "") usedNames.erase(name);
}

std::size_t NPC::getCreatedCount () {
    return createdCount;
}

Point<int> NPC::getPos () const {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return position;
}

std::string NPC::getName () const {
    return name;
}

NPCType NPC::getType () const {
    return type;
}

char NPC::getSprite () const {
    return sprite;
}

std::size_t NPC::getMovePoints () const {
    return movePoints;
}

std::size_t NPC::getKillDistance () const {
    return killDistance;
}

bool NPC::isClose (const std::shared_ptr<NPC> &other) {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return (position - other->position).abs() < killDistance;
}

bool NPC::isAlive () {
    std::shared_lock<std::shared_mutex> lock(mtx);
    return alive;
}

void NPC::kill () {
    std::lock_guard<std::shared_mutex> lock(mtx);
    alive = false;
}

std::ostream& operator<<(std::ostream &os, NPC &npc) {
    return npc.print(os);
} 