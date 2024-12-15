#pragma once
#include <iostream>
#include <fstream>
#include "../Observer.h"
#include "../NPC.h"

class ObserverFile : public IObserver<FightEvent> {
    private:
        std::ofstream file;
    
    protected:
        void notify (FightEvent event) override;

    public:
        ObserverFile (std::string filename);
        ~ObserverFile ();
};