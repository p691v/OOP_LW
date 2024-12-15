#include <gtest/gtest.h>

#include "../include/utils.h"
#include "../include/point.h"
#include "../include/NPC.h"
#include "../include/NPCs/Bandit.h"
#include "../include/NPCs/Orc.h"
#include "../include/NPCs/Werewolf.h"
#include "../include/factories/FactoryRandom.h"
#include "../include/factories/FactoryFile.h"

TEST(utils, cmp_double_eq) {
    double a = 0.1 + 0.2;
    double b = 0.3;
    bool result = Utils::cmpDouble(a, b);
    
    ASSERT_TRUE(result == true);
}

TEST(utils, cmp_double_not_eq) {
    double a = 0.1 + 0.2;
    double b = 0.31;
    bool result = Utils::cmpDouble(a, b);
    
    ASSERT_TRUE(result == false);
}

TEST(point, getter_x) {
    Point point(2.0, 3.0);
    double getXRes = point.getX();

    ASSERT_TRUE(getXRes == 2.0);
}

TEST(point, getter_y) {
    Point point(2.0, 3.0);
    double getYRes = point.getY();

    ASSERT_TRUE(getYRes == 3.0);
}

TEST(point, cmp_eq) {
    Point a(0.0, 3.0);
    Point b(0.0, 1.0 + 2.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == true);
}

TEST(point, cmp_not_eq_x) {
    Point a(0.0, 3.0);
    Point b(1.0, 3.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == false);
}

TEST(point, cmp_not_eq_y) {
    Point a(0.0, 3.0);
    Point b(0.0, -1.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == false);
}

TEST(point, cmp_not_eq_x_y) {
    Point a(0.0, 3.0);
    Point b(2.0, -1.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == false);
}

TEST(point, default_constructor) {
    Point<double> point;
    Point pointRef(0.0, 0.0);
    bool result = point == pointRef; 

    ASSERT_TRUE(result == true);
}

TEST(point, single_number_constructor) {
    Point point(1.0);
    Point pointRef(1.0, 1.0);
    bool result = point == pointRef; 

    ASSERT_TRUE(result == true);
}

TEST(point, copy) {
    Point pointSrc(1.0, 2.0);
    Point point{pointSrc};
    bool result = point == pointSrc; 

    ASSERT_TRUE(result == true);
}

TEST(point, assigment) {
    Point pointSrc(1.0, 2.0);
    Point point = pointSrc;
    bool result = point == pointSrc; 

    ASSERT_TRUE(result == true);
}

TEST(point, sum) {
    Point a(1.0, 2.2);
    Point b(3.0, -8.5);
    Point sumRef(4.0, -6.3);
    Point sum = a + b;

    ASSERT_TRUE(sum == sumRef);
}

TEST(point, diff) {
    Point a(1.0, 2.2);
    Point b(3.0, -8.5);
    Point diffRef(-2.0, 10.7);
    Point diff = a - b;

    ASSERT_TRUE(diff == diffRef);
}

TEST(point, product) {
    Point a(1.5, -2.2);
    double k = -2.0;
    Point productRef(-3.0, 4.4);
    Point product = a * k;

    ASSERT_TRUE(product == productRef);
}

TEST(point, abs) {
    Point a(3.0, -4.0);
    double absRef = 5.0;
    double abs = a.abs();

    ASSERT_TRUE(Utils::cmpDouble(absRef, abs));
}

TEST(npc, unique_name_error) {
    ASSERT_THROW({
        Bandit pirate(Point(3, 5), "npc");
        Werewolf pirate2(Point(3, 5), "npc");
    }, std::logic_error);
}

TEST(npc, unique_name_free) {
    ASSERT_NO_THROW({
        {
            Bandit pirate(Point(3, 5), "npc_free");
        }
        {
            Werewolf pirate2(Point(3, 5), "npc_free");
        }
    });
}

TEST(npc, enough_close) {
    Bandit pirate1(Point(1, 2), "pirate1");
    std::shared_ptr<Bandit> pirate2 = std::make_shared<Bandit>(Point(5, 5), "pirate2");
    
    bool result = pirate1.isClose(pirate2);

    ASSERT_TRUE(result == true);
}

TEST(npc, not_enough_close) {
    Bandit pirate1(Point(1, 2), "pirate1");
    std::shared_ptr<Bandit> pirate2 = std::make_shared<Bandit>(Point(6, 5), "pirate2");
    
    bool result = pirate1.isClose(pirate2);

    ASSERT_TRUE(result == false);
}

TEST(npc, getter_pos) {
    Bandit pirate1(Point(1, 2), "pirate1");

    Point result = pirate1.getPos();

    ASSERT_TRUE(result == Point(1, 2));
}

TEST(npc, getter_name) {
    Bandit pirate1(Point(1, 2), "pirate1");

    std::string result = pirate1.getName();

    ASSERT_TRUE(result == "pirate1");
}

TEST(rakyat, accept_true) {
    std::shared_ptr<NPC> attacker = std::make_shared<Bandit>(Point(6, 5), "attacker");
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(Point(6, 5), "defender");

    bool result = defender->accept(attacker);

    ASSERT_TRUE(result == true);
}

TEST(rakyat, accept_false) {
    std::shared_ptr<NPC> attacker = std::make_shared<Bandit>(Point(6, 5), "attacker");
    std::shared_ptr<NPC> defender = std::make_shared<Werewolf>(Point(6, 5), "defender");

    bool result = defender->accept(attacker);

    ASSERT_TRUE(result == false);
}

TEST(pirate, constructor) {
    Bandit pirate(Point(3, 5), "pirate.constructor");

    NPCType result = pirate.getType();

    ASSERT_TRUE(result == NPCType::BanditType);
}

TEST(pirate, win_pirate) {
    Bandit attacker(Point(3, 5), "attacker");
    Bandit defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == false);
}

TEST(pirate, win_privateer) {
    Bandit attacker(Point(3, 5), "attacker");
    Orc defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == true);
}

TEST(pirate, win_rakyat) {
    Bandit attacker(Point(3, 5), "attacker");
    Werewolf defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == false);
}

TEST(privateer, constructor) {
    Orc privateer(Point(3, 5), "privateer.constructor");

    NPCType result = privateer.getType();

    ASSERT_TRUE(result == NPCType::OrcType);
}

TEST(privateer, win_pirate) {
    Orc attacker(Point(3, 5), "attacker");
    Bandit defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == false);
}

TEST(privateer, win_privateer) {
    Orc attacker(Point(3, 5), "attacker");
    Orc defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == false);
}

TEST(privateer, win_rakyat) {
    Orc attacker(Point(3, 5), "attacker");
    Werewolf defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == true);
}

TEST(rakyat, constructor) {
    Werewolf rakyat(Point(3, 5), "rakyat.constructor");

    NPCType result = rakyat.getType();

    ASSERT_TRUE(result == NPCType::WerewolfType);
}

TEST(rakyat, win_pirate) {
    Werewolf attacker(Point(3, 5), "attacker");
    Bandit defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == true);
}

TEST(rakyat, win_privateer) {
    Werewolf attacker(Point(3, 5), "attacker");
    Orc defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == false);
}

TEST(rakyat, win_rakyat) {
    Werewolf attacker(Point(3, 5), "attacker");
    Werewolf defender(Point(3, 5), "defender");

    bool result = attacker.fight(defender);

    ASSERT_TRUE(result == false);
}

TEST(random_factory, create_pirate) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreatePirate();
    NPCType result = npc->getType();

    ASSERT_TRUE(result == NPCType::BanditType);
}

TEST(random_factory, create_privateer) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreatePrivateer();
    NPCType result = npc->getType();

    ASSERT_TRUE(result == NPCType::OrcType);
}

TEST(random_factory, create_rakyat) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreateRakyat();
    NPCType result = npc->getType();

    ASSERT_TRUE(result == NPCType::WerewolfType);
}

TEST(random_factory, create_pirate_type) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreateNPC(NPCType::BanditType);
    NPCType result = npc->getType();

    ASSERT_TRUE(result == NPCType::BanditType);
}

TEST(random_factory, create_privateer_type) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreateNPC(NPCType::OrcType);
    NPCType result = npc->getType();

    ASSERT_TRUE(result == NPCType::OrcType);
}

TEST(random_factory, create_rakyat_type) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreateNPC(NPCType::WerewolfType);
    NPCType result = npc->getType();

    ASSERT_TRUE(result == NPCType::WerewolfType);
}

TEST(random_factory, error_type) {
    FactoryRandom factory(500, 100);

    ASSERT_THROW(factory.CreateNPC(NPCType::Unknown), std::logic_error);
}

TEST(random_factory, position) {
    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> npc = factory.CreateRandomNPC();
    Point pos = npc->getPos();
    
    bool result = 0 <= pos.getX() && pos.getX() < 500 && 0 <= pos.getY() && pos.getY() < 100;

    ASSERT_TRUE(result == true);
}

TEST(factory_file, factory_file) {
    Point<int> pos1, pos2, pos3;
    std::string name1, name2, name3;
    {
        FactoryFile::NPCSaver saver("test_save.save", 3);

        FactoryRandom factory(500, 100);

        std::shared_ptr<NPC> npc1 = factory.CreatePirate();
        std::shared_ptr<NPC> npc2 = factory.CreatePrivateer();
        std::shared_ptr<NPC> npc3 = factory.CreateRakyat();

        pos1 = npc1->getPos();
        pos2 = npc2->getPos();
        pos3 = npc3->getPos();

        name1 = npc1->getName();
        name2 = npc2->getName();
        name3 = npc3->getName();

        saver.saveNPC(npc1);
        saver.saveNPC(npc2);
        saver.saveNPC(npc3);
    }

    {
        FactoryFile factory("test_save.save");
        
        std::shared_ptr<NPC> npc1 = factory.CreateNPCFromFile();
        std::shared_ptr<NPC> npc2 = factory.CreateNPCFromFile();
        std::shared_ptr<NPC> npc3 = factory.CreateNPCFromFile();

        bool result = npc1->getType() == NPCType::BanditType &&
        npc1->getName() == name1 &&
        npc1->getPos() == pos1 &&
        npc2->getType() == NPCType::OrcType &&
        npc2->getName() == name2 &&
        npc2->getPos() == pos2 &&
        npc3->getType() == NPCType::WerewolfType &&
        npc3->getName() == name3 &&
        npc3->getPos() == pos3;

        ASSERT_TRUE(result == true);
    }
}

TEST(observer, observer) {
    FightEvent event("", "");

    class ConcreteObserver : public IObserver<FightEvent> {
        private:
            FightEvent *eventPtr;
        
        protected:
            void notify (FightEvent event) override {
                eventPtr->attackerName = event.attackerName;
                eventPtr->defenderName = event.defenderName;
            } 

        public:
            ConcreteObserver (FightEvent *ptr) : eventPtr{ptr} {};  
    };

    std::shared_ptr<ConcreteObserver> observer = std::make_shared<ConcreteObserver>(&event);

    FactoryRandom factory(500, 100);

    std::shared_ptr<NPC> attacker = std::make_shared<Bandit>(Point(3, 5), "attacker");
    std::shared_ptr<NPC> defender = std::make_shared<Orc>(Point(3, 5), "defender");

    attacker->subscribe(observer);
    defender->accept(attacker);

    bool result = event.attackerName == "attacker" && event.defenderName == "defender";

    ASSERT_TRUE(result);
}

int main (int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}