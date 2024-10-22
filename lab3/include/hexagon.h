#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "utils.h"
#include "point.h"
#include "figure.h"

class Hexagon : public Figure {
    private:
        Point a;
        Point b;
        Point c;
        Point d;
        Point e;
        Point f;

        static void checkCorrect (Point a, Point b, Point c, Point d, Point e, Point f);

    protected:
        std::ostream& print (std::ostream& os) const override;
        std::istream& input (std::istream& is) override;

    public:
        Hexagon ();
        Hexagon (Point pA, Point pB, Point pC, Point pD, Point pE, Point pF);
        Hexagon (const Hexagon &other);
        Hexagon (Hexagon &&other);
        Hexagon& operator= (const Hexagon &other);
        Hexagon& operator= (Hexagon &&other);

        Point calcRotationCenter () override;
        operator double() override;

        bool operator== (const Hexagon &other) const;
        bool operator&& (const Hexagon &other) const;

    friend std::ostream& operator<< (std::ostream& os, const Hexagon &hexagon);
    friend std::istream& operator>> (std::istream& is, Hexagon &hexagon);
};

std::ostream& operator<< (std::ostream& os, const Hexagon &hexagon);
std::istream& operator>> (std::istream& is, Hexagon &hexagon);