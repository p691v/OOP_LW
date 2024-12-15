#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <memory>
#include "utils.h"
#include "point.h"
#include "figure.h"

template <RealType T>
class Octagon : public Figure<T> {
    private:
        std::unique_ptr<Point<T>> a{nullptr};
        std::unique_ptr<Point<T>> b{nullptr};
        std::unique_ptr<Point<T>> c{nullptr};
        std::unique_ptr<Point<T>> d{nullptr};
        std::unique_ptr<Point<T>> e{nullptr};
        std::unique_ptr<Point<T>> f{nullptr};
        std::unique_ptr<Point<T>> g{nullptr};
        std::unique_ptr<Point<T>> h{nullptr};
        
        void checkCorrect (Point<T> a, Point<T> b, Point<T> c, Point<T> d, Point<T> e, Point<T> f, Point<T> g, Point<T> h) {
            double AB = (a - b).abs();
            double BC = (b - c).abs();
            double CD = (c - d).abs();
            double DE = (d - e).abs();
            double EF = (e - f).abs();
            double FG = (f - g).abs();
            double GH = (g - h).abs();
            double HA = (h - a).abs();

            double AE = (a - e).abs();
            double BF = (b - f).abs();
            double CG = (c - g).abs();
            double DH = (d - h).abs();

            double phi = M_PI / 8.0 * 3.0;
            double diagonal = AB * (cos(phi) + sin(phi)) * 2.0;

            bool sidesEq = Utils::cmpDouble(AB, BC) && Utils::cmpDouble(BC, CD) && Utils::cmpDouble(CD, DE) &&
            Utils::cmpDouble(DE, EF) && Utils::cmpDouble(EF, FG) && Utils::cmpDouble(FG, GH) && Utils::cmpDouble(GH, HA);

            bool diagonalsCheck = Utils::cmpDouble(AE, diagonal) && Utils::cmpDouble(BF, diagonal) &&
            Utils::cmpDouble(CG, diagonal) && Utils::cmpDouble(DH, diagonal);

            if (!(sidesEq && diagonalsCheck)) {
                throw std::invalid_argument("Invalid point<T>s for a regular octagon.");
            }
        }
    
    protected:
        std::ostream& print (std::ostream& os) const override {
            os << "Octagon (" << std::endl;
            os << "\tA = " << *a << std::endl;
            os << "\tB = " << *b << std::endl;
            os << "\tC = " << *c << std::endl;
            os << "\tD = " << *d << std::endl;
            os << "\tE = " << *e << std::endl;
            os << "\tF = " << *f << std::endl;
            os << "\tG = " << *g << std::endl;
            os << "\tH = " << *h << std::endl;
            os << ")";
            return os;
        }

        std::istream& input (std::istream& is) override {
            Point<T> pA, pB, pC, pD, pE, pF, pG, pH;

            std::cout << "Input Octagon (" << std::endl;

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

            std::cout << "Input point G = ";
            is >> pG;

            std::cout << "Input point H = ";
            is >> pH;

            std::cout << ")" << std::endl;

            checkCorrect(pA, pB, pC, pD, pE, pF, pG, pH);

            *a = pA;
            *b = pB;
            *c = pC;
            *d = pD;
            *e = pE;
            *f = pF;
            *g = pG;
            *h = pH;

            return is;
        }

    public:
        Octagon () {
            a = std::make_unique<Point<T>>(cos(0.0), sin(0.0));
            b = std::make_unique<Point<T>>(cos(M_PI / 4.0), sin(M_PI / 4.0));
            c = std::make_unique<Point<T>>(cos(M_PI / 2.0), sin(M_PI / 2.0));
            d = std::make_unique<Point<T>>(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0));
            e = std::make_unique<Point<T>>(cos(M_PI), sin(M_PI));
            f = std::make_unique<Point<T>>(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0));
            g = std::make_unique<Point<T>>(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0));
            h = std::make_unique<Point<T>>(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0));    
        }

        Octagon (Point<T> pA, Point<T> pB, Point<T> pC, Point<T> pD, Point<T> pE, Point<T> pF, Point<T> pG, Point<T> pH) {
            checkCorrect(pA, pB, pC, pD, pE, pF, pG, pH);

            a = std::make_unique<Point<T>>(pA);
            b = std::make_unique<Point<T>>(pB);
            c = std::make_unique<Point<T>>(pC);
            d = std::make_unique<Point<T>>(pD);
            e = std::make_unique<Point<T>>(pE);
            f = std::make_unique<Point<T>>(pF);
            g = std::make_unique<Point<T>>(pG);
            h = std::make_unique<Point<T>>(pH);
        }

        Octagon (const Octagon &other) {
            a = std::make_unique<Point<T>>(*other.a);
            b = std::make_unique<Point<T>>(*other.b);
            c = std::make_unique<Point<T>>(*other.c);
            d = std::make_unique<Point<T>>(*other.d);
            e = std::make_unique<Point<T>>(*other.e);
            f = std::make_unique<Point<T>>(*other.f);
            g = std::make_unique<Point<T>>(*other.g);
            h = std::make_unique<Point<T>>(*other.h);
        }

        Octagon (Octagon &&other) {
            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
            d = std::move(other.d);
            e = std::move(other.e);
            f = std::move(other.f);
            g = std::move(other.g);
            h = std::move(other.h);        
        }

        Octagon& operator= (const Octagon &other) {
            if (this == &other) return *this;
            *a = *other.a;
            *b = *other.b;
            *c = *other.c;
            *d = *other.d;
            *e = *other.e;
            *f = *other.f;
            *g = *other.g;
            *h = *other.h;
            return *this;
        }

        Octagon& operator= (Octagon &&other) {
            a.reset();
            b.reset();
            c.reset();
            d.reset();
            e.reset();
            f.reset();
            g.reset();
            h.reset();

            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
            d = std::move(other.d);
            e = std::move(other.e);
            f = std::move(other.f);
            g = std::move(other.g);
            h = std::move(other.h);
            
            return *this;
        }

        Point<T> calcRotationCenter () override {
            Point<T> mid = (*a + *b + *c + *d + *e + *f + *g + *h) * (1.0 / 8.0);
            return mid;
        }

        operator double () override {
            return (*a - *e).abs() * sin(M_PI / 4.0) * 4.0;
        }

        std::unique_ptr<Array<Point<double>>> getPointsArray () override {
            std::unique_ptr<Array<Point<double>>> points = std::make_unique<Array<Point<double>>>();

            points->append(Point<double>(*a));
            points->append(Point<double>(*b));
            points->append(Point<double>(*c));
            points->append(Point<double>(*d));
            points->append(Point<double>(*e));
            points->append(Point<double>(*f));
            points->append(Point<double>(*g));
            points->append(Point<double>(*h));

            return points;
        }

        bool operator== (const Octagon &other) const {
            return *a == *other.a && *b == *other.b && *c == *other.c && *d == *other.d && 
                *e == *other.e && *f == *other.f && *g == *other.g && *h == *other.h; 
        }

        bool operator&& (const Octagon &other) const {
            return Utils::cmpDouble((*a - *b).abs(), (*other.a - *other.b).abs());
        }

    friend std::ostream& operator<< (std::ostream& os, const Octagon &octagon) {
        return octagon.print(os);
    }

    friend std::istream& operator>> (std::istream& is, Octagon &octagon) {
        return octagon.input(is);
    }
};