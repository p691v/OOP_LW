#pragma once
#include "../NPC.h"
#include "Bandit.h"
#include "Orc.h"

class Werewolf : public NPC {
    public:
        Werewolf (Point<int> pos, std::string name);

        bool fight (const Bandit &other) override;
        bool fight (const Orc &other) override;
        bool fight (const Werewolf &other) override;

        bool accept (std::shared_ptr<NPC> other) override;

        std::ostream& print (std::ostream &os) override;

        friend std::ostream& operator<<(std::ostream &os, Werewolf &rakyat);
};