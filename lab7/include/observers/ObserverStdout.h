#pragma once
#include <iostream>
#include "../Observer.h"
#include "../NPC.h"
#include "../Printer.h"

class ObserverStdout : public IObserver<FightEvent> {
    protected:
        void notify (FightEvent event) override;
};