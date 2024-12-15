#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdexcept>
#include "utils.h"
#include "point.h"
#include "figure.h"

class Triangle : public Figure {
    private:
        Point a;
        Point b;
        Point c;

        static void validate (Point a, Point b, Point c);

    protected:
        std::ostream& print (std::ostream& os) const override;
        std::istream& input (std::istream& is) override;

    public:
        Triangle ();
        Triangle (Point pA, Point pB, Point pC);
        Triangle (const Triangle &other);
        Triangle (Triangle &&other);
        Triangle& operator= (const Triangle &other);
        Triangle& operator= (Triangle &&other);        

        Point calcRotationCenter () override;
        operator double () override;

        bool operator== (const Triangle &other) const;
        bool operator&& (const Triangle &other) const;

    friend std::ostream& operator<< (std::ostream& os, const Triangle &triangle);
    friend std::istream& operator>> (std::istream& is, Triangle &triangle);
};

std::ostream& operator<< (std::ostream& os, const Triangle &triangle);
std::istream& operator>> (std::istream& is, Triangle &triangle);