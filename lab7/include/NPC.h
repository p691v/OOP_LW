#pragma once
#include <set>
#include <iostream>
#include <string>
#include <memory>
#include <shared_mutex>
#include <cstdlib>
#include "Observer.h"
#include "point.h"

enum NPCType {
    Unknown = 0,
    BanditType,
    OrcType,
    WerewolfType
};

class NPC;
class Bandit;
class Orc;
class Werewolf;

struct FightEvent {
    std::string attackerName;
    std::string defenderName;

    FightEvent (std::string attacker, std::string defender) : 
        attackerName{attacker}, defenderName{defender} {};
};

class NPC : public Observable<FightEvent> {
    private:
        static std::set<std::string> usedNames;
        static std::size_t createdCount;

        std::string name;
        NPCType type;
        char sprite;
        
        std::size_t movePoints;
        std::size_t killDistance;

        bool alive;

    protected: 
        mutable std::shared_mutex mtx;

        Point<int> position;

        void fightNotify (std::string defenderName);

    public:
        static std::size_t getCreatedCount ();

        NPC (Point<int> pos, std::string npcName, NPCType npcType, std::size_t move, std::size_t kill, char npcSprite);
        virtual ~NPC ();

        std::string getName () const;
        Point<int> getPos () const;
        NPCType getType () const;
        char getSprite () const;
        std::size_t getMovePoints () const;
        std::size_t getKillDistance () const;

        bool isClose (const std::shared_ptr<NPC> &other);

        virtual bool fight (const Bandit &other) = 0;
        virtual bool fight (const Orc &other) = 0;
        virtual bool fight (const Werewolf &other) = 0;

        virtual bool accept (std::shared_ptr<NPC> other) = 0;

        virtual void move (std::size_t mapWidth, std::size_t mapHeight) = 0;

        virtual std::ostream& print (std::ostream &os) = 0;

        bool isAlive ();
        void kill ();

        friend std::ostream& operator<<(std::ostream &os, NPC &npc); 
};