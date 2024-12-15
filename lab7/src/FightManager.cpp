#include "../include/FightManager.h"
#include "../include/DiceBag.h"

void FightManager::addFightPrompt (FightPrompt &&prompt) {
    std::lock_guard<std::shared_mutex> lock(mtx);

    prompts.push(prompt);
}

void FightManager::organizeFight (FightPrompt &prompt) {
    if (!prompt.attacker->isAlive() || !prompt.defender->isAlive()) return;

    std::size_t attackPoints = DiceBag::rollDiceOfFate<6>();
    std::size_t defencePoints = DiceBag::rollDiceOfFate<6>();

    if (attackPoints > defencePoints) {
        prompt.defender->kill();
        notifySubs(MurderEvent(prompt.attacker->getName(), prompt.defender->getName()));
    } 
}

void FightManager::operator() (const bool &gameRunning) {
    while (gameRunning) {
        std::shared_lock<std::shared_mutex> lockRead(mtx);
        if (prompts.empty()) continue;
        
        lockRead.unlock();
        std::shared_lock<std::shared_mutex> lockWrite(mtx);

        organizeFight(prompts.front());
        prompts.pop();
    }
}
