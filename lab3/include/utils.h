#pragma once
#include <math.h>

class Utils {
    private:
        static constexpr double EPS = 0.0001;

    public:
        static bool cmpDouble (double a, double b);
        static double triangleArea (double a, double b, double c);
};
