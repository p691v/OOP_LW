#pragma once
#include <iostream>
#include "../Observer.h"
#include "../NPC.h"

class ObserverStdout : public IObserver<FightEvent> {
    protected:
        void notify (FightEvent event) override;
};