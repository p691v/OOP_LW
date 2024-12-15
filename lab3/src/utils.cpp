#include "../include/utils.h"

bool Utils::cmpDouble (double a, double b) {
    return abs(a - b) < EPS;
}

double Utils::triangleArea (double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

