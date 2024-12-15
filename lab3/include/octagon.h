#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "utils.h"
#include "point.h"
#include "figure.h"

class Octagon : public Figure {
    private:
        Point a;
        Point b;
        Point c;
        Point d;
        Point e;
        Point f;
        Point g;
        Point h;

        static void validate (Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h);

    protected:
        std::ostream& print (std::ostream& outp) const override;
        std::istream& input (std::istream& inp) override;

    public:
        Octagon ();
        Octagon (Point pA, Point pB, Point pC, Point pD, Point pE, Point pF, Point pG, Point pH);
        Octagon (const Octagon &other);
        Octagon (Octagon &&other);
        Octagon& operator= (const Octagon &other);
        Octagon& operator= (Octagon &&other);

        Point calcRotationCenter () override;
        operator double () override;

        bool operator== (const Octagon &other) const;
        bool operator&& (const Octagon &other) const;

    friend std::ostream& operator<< (std::ostream& os, const Octagon &octagon);
    friend std::istream& operator>> (std::istream& is, Octagon &octagon);
};

std::ostream& operator<< (std::ostream& os, const Octagon &octagon);
std::istream& operator>> (std::istream& is, Octagon &octagon);