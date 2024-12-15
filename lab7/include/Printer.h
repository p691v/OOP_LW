#pragma once
#include <sstream>
#include <iostream>
#include <mutex>

class Printer : public std::stringstream {
    private:
        static std::mutex mtx;

    public:
        ~Printer ();
};