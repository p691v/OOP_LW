#pragma once
#include <iostream>
#include "../Observer.h"
#include "../NPC.h"
#include "../Printer.h"
#include "../FightManager.h"

class ObserverMurderStdout : public IObserver<MurderEvent> {
    protected:
        void notify (MurderEvent event) override;
};