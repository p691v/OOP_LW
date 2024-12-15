#pragma once
#include <queue>
#include <memory>
#include <shared_mutex>
#include "NPC.h"
#include "Observer.h"

struct MurderEvent {
    std::string killerName;
    std::string victimName;

    MurderEvent (std::string killer, std::string victim) : 
        killerName{killer}, victimName{victim} {};
};

class FightManager : public Observable<MurderEvent> {
    public:
        struct FightPrompt {
            std::shared_ptr<NPC> attacker;
            std::shared_ptr<NPC> defender;

            FightPrompt (std::shared_ptr<NPC> attackerPtr, std::shared_ptr<NPC> defenderPtr) : 
                attacker{attackerPtr}, defender{defenderPtr} {};
        };

    private:
        std::queue<FightPrompt> prompts;
        std::shared_mutex mtx;

        void organizeFight (FightPrompt &prompt);

    public:
        FightManager () = default;
        
        void addFightPrompt (FightPrompt &&prompt);
        void operator() (const bool &gameRunning);
};