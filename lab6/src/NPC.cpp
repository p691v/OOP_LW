#include <stdexcept>
#include "../include/NPC.h"

std::set<std::string> NPC::usedNames;
std::size_t NPC::createdCount = 0;

void NPC::fightNotify (std::string defenderName, bool meWin) {
    notifySubs(FightEvent(getName(), defenderName, meWin));
}

NPC::NPC (Point<int> pos, std::string npcName, NPCType npcType) {
    name = "";

    if (usedNames.contains(npcName)) {
        throw std::logic_error(std::string("NPC with name ") + npcName + " already exists.");
    }

    usedNames.insert(npcName);

    position = pos;
    name = npcName;
    type = npcType;
    
    createdCount++;
}

NPC::~NPC () {
    if (name != "") usedNames.erase(name);
}

std::size_t NPC::getCreatedCount () {
    return createdCount;
}

std::string NPC::getName () const {
    return name;
}

Point<int> NPC::getPos () const {
    return position;
}

NPCType NPC::getType () const {
    return type;
}

bool NPC::isClose (const std::shared_ptr<NPC> &other, double closeDistance) {
    return (position - other->position).abs() < closeDistance;
}

std::ostream& operator<<(std::ostream &os, NPC &npc) {
    return npc.print(os);
} 