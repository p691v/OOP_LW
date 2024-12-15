#pragma once
#include <cstdlib>
#include <stdexcept>
#include "../NPC.h"
#include "../NPCs/Bandit.h"
#include "../NPCs/Orc.h"
#include "../NPCs/Werewolf.h"

class FactoryRandom {
    private:
        std::size_t mapWidth;
        std::size_t mapHeight;

        Point<int> getRandomPosition ();

        static std::string makeNameUnique (std::string name);
    
    public:
        FactoryRandom (std::size_t width, std::size_t height);

        std::shared_ptr<NPC> CreatePirate ();
        std::shared_ptr<NPC> CreatePrivateer ();
        std::shared_ptr<NPC> CreateRakyat ();

        std::shared_ptr<NPC> CreateNPC (NPCType type);
        std::shared_ptr<NPC> CreateRandomNPC ();
};