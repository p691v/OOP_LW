#include "../../include/factories/FactoryRandom.h"

Point<int> FactoryRandom::getRandomPosition () {
    int posX = std::rand() % mapWidth;
    int posY = std::rand() % mapHeight;
    return Point(posX, posY);
}

std::string FactoryRandom::makeNameUnique (std::string name) {
    return name + " #" + std::to_string(NPC::getCreatedCount());
}

FactoryRandom::FactoryRandom (std::size_t width, std::size_t height) : mapWidth{width}, mapHeight{height} {}

std::shared_ptr<NPC> FactoryRandom::CreatePirate () {
    return std::make_shared<Bandit>(getRandomPosition(), makeNameUnique("Bandit"));
}

std::shared_ptr<NPC> FactoryRandom::CreatePrivateer () {
    return std::make_shared<Orc>(getRandomPosition(), makeNameUnique("Orc"));
}

std::shared_ptr<NPC> FactoryRandom::CreateRakyat () {
    return std::make_shared<Werewolf>(getRandomPosition(), makeNameUnique("Werewolf"));
}

std::shared_ptr<NPC> FactoryRandom::CreateNPC (NPCType type) {
    switch (type) {
        case NPCType::BanditType:
            return CreatePirate();        
        
        case NPCType::OrcType:
            return CreatePrivateer();        
        
        case NPCType::WerewolfType:
            return CreateRakyat();        
        
        default:
            throw std::logic_error("Unknown NPC type.");
    }
}

std::shared_ptr<NPC> FactoryRandom::CreateRandomNPC () {
    NPCType type = NPCType(std::rand() % 3 + 1);
    return CreateNPC(type);
}
