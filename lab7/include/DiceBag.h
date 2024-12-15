#pragma once
#include <cstdlib>

class DiceBag {
    public:
        template <std::size_t faces>
        static std::size_t rollDiceOfFate () {
            return std::rand() % faces;
        } 
};