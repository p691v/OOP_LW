#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <memory>
#include "utils.h"
#include "point.h"
#include "figure.h"

template <RealType T>
class Hexagon : public Figure<T> {
    private:
        std::unique_ptr<Point<T>> a{nullptr};
        std::unique_ptr<Point<T>> b{nullptr};
        std::unique_ptr<Point<T>> c{nullptr};
        std::unique_ptr<Point<T>> d{nullptr};
        std::unique_ptr<Point<T>> e{nullptr};
        std::unique_ptr<Point<T>> f{nullptr};

        static void checkCorrect (Point<T> a, Point<T> b, Point<T> c, Point<T> d, Point<T> e, Point<T> f) {
            double AB = (a - b).abs();
            double BC = (b - c).abs();
            double CD = (c - d).abs();
            double DE = (d - e).abs();
            double EF = (e - f).abs();
            double FA = (f - a).abs();

            double AD = (a - d).abs();
            double BE = (b - e).abs();
            double CF = (c - f).abs();

            bool sidesEq = Utils::cmpDouble(AB, BC) && Utils::cmpDouble(BC, CD) && Utils::cmpDouble(CD, DE) &&
                Utils::cmpDouble(DE, EF) && Utils::cmpDouble(EF, FA);

            bool diagonalsCheck = Utils::cmpDouble(AB * 2.0, AD) && Utils::cmpDouble(AB * 2.0, BE) && Utils::cmpDouble(AB * 2.0, CF);

            if (!(sidesEq && diagonalsCheck)) {
                throw std::invalid_argument("Invalid points for a regular hexagon.");
            }
        }

    protected:
        std::ostream& print (std::ostream& os) const override {
            os << "Hexagon (" << std::endl;
            os << "\tA = " << *a << std::endl;
            os << "\tB = " << *b << std::endl;
            os << "\tC = " << *c << std::endl;
            os << "\tD = " << *d << std::endl;
            os << "\tE = " << *e << std::endl;
            os << "\tF = " << *f << std::endl;
            os << ")";
            return os;
        }

        std::istream& input (std::istream& is) override {
            Point<T> pA, pB, pC, pD, pE, pF;

            std::cout << "Input Hexagon (" << std::endl;

            std::cout << "Input point A = ";
            is >> pA;

            std::cout << "Input point B = ";
            is >> pB;

            std::cout << "Input point C = ";
            is >> pC;

            std::cout << "Input point D = ";
            is >> pD;

            std::cout << "Input point E = ";
            is >> pE;

            std::cout << "Input point F = ";
            is >> pF;

            std::cout << ")" << std::endl;

            checkCorrect(pA, pB, pC, pD, pE, pF);

            *a = pA;
            *b = pB;
            *c = pC;
            *d = pD;
            *e = pE;
            *f = pF;

            return is;
        }

    public:
        Hexagon ()  {
            a = std::make_unique<Point<T>>(cos(0.0), sin(0.0));
            b = std::make_unique<Point<T>>(cos(M_PI / 3.0), sin(M_PI / 3.0));
            c = std::make_unique<Point<T>>(cos(M_PI * 2.0 / 3.0), sin(M_PI * 2.0 / 3.0));
            d = std::make_unique<Point<T>>(cos(M_PI), sin(M_PI));
            e = std::make_unique<Point<T>>(cos(M_PI * 4.0 / 3.0), sin(M_PI * 4.0 / 3.0));
            f = std::make_unique<Point<T>>(cos(M_PI * 5.0 / 3.0), sin(M_PI * 5.0 / 3.0));
        }

        Hexagon (Point<T> pA, Point<T> pB, Point<T> pC, Point<T> pD, Point<T> pE, Point<T> pF) {
            checkCorrect(pA, pB, pC, pD, pE, pF);

            a = std::make_unique<Point<T>>(pA);
            b = std::make_unique<Point<T>>(pB);
            c = std::make_unique<Point<T>>(pC);
            d = std::make_unique<Point<T>>(pD);
            e = std::make_unique<Point<T>>(pE);
            f = std::make_unique<Point<T>>(pF);
        }

        Hexagon (const Hexagon &other) {
            a = std::make_unique<Point<T>>(*other.a);
            b = std::make_unique<Point<T>>(*other.b);
            c = std::make_unique<Point<T>>(*other.c);
            d = std::make_unique<Point<T>>(*other.d);
            e = std::make_unique<Point<T>>(*other.e);
            f = std::make_unique<Point<T>>(*other.f);
        }
        
        Hexagon (Hexagon &&other) {
            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
            d = std::move(other.d);
            e = std::move(other.e);
            f = std::move(other.f);        
        }

        Hexagon& operator= (const Hexagon &other) {
            if (this == &other) return *this;
            *a = *other.a;
            *b = *other.b;
            *c = *other.c;
            *d = *other.d;
            *e = *other.e;
            *f = *other.f;
            return *this;
        }

        Hexagon& operator= (Hexagon &&other) {
            a.reset();
            b.reset();
            c.reset();
            d.reset();
            e.reset();
            f.reset();

            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
            d = std::move(other.d);
            e = std::move(other.e);
            f = std::move(other.f);
            
            return *this;
        }

        Point<T> calcRotationCenter () override {
            Point<T> mid = (*a + *b + *c + *d + *e + *f) * (1.0 / 6.0);
            return mid;
        }

        operator double() override {
            return (*a - *b).abs() * sin(M_PI / 3) * 6.0;
        }

        std::unique_ptr<Array<Point<double>>> getPointsArray () override {
            std::unique_ptr<Array<Point<double>>> points = std::make_unique<Array<Point<double>>>();

            points->append(Point<double>(*a));
            points->append(Point<double>(*b));
            points->append(Point<double>(*c));
            points->append(Point<double>(*d));
            points->append(Point<double>(*e));
            points->append(Point<double>(*f));

            return points;
        }

        bool operator== (const Hexagon &other) const {
            return *a == *other.a && *b == *other.b && *c == *other.c && *d == *other.d && *e == *other.e && *f == *other.f;
        }   

        bool operator&& (const Hexagon &other) const {
            return Utils::cmpDouble((*a - *b).abs(), (*other.a - *other.b).abs());
        }

    friend std::ostream& operator<< (std::ostream& os, const Hexagon &hexagon) {
        return hexagon.print(os);
    }

    friend std::istream& operator>> (std::istream& is, Hexagon &hexagon) {
        return hexagon.input(is);
    }
};