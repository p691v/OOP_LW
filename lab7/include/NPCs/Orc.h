#pragma once
#include "../NPC.h"
#include "Bandit.h"
#include "Werewolf.h"

class Orc : public NPC {
    public:
        Orc (Point<int> pos, std::string name);

        bool fight (const Bandit &other) override;
        bool fight (const Orc &other) override;
        bool fight (const Werewolf &other) override;

        bool accept (std::shared_ptr<NPC> other) override;

        void move (std::size_t mapWidth, std::size_t mapHeight) override;

        std::ostream& print (std::ostream &os) override;

        friend std::ostream& operator<<(std::ostream &os, Orc &privateer);
};