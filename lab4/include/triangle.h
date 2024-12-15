#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdexcept>
#include <memory>
#include "utils.h"
#include "point.h"
#include "figure.h"

template <RealType T>
class Triangle : public Figure<T> {
    private:
        std::unique_ptr<Point<T>> a{nullptr};
        std::unique_ptr<Point<T>> b{nullptr};
        std::unique_ptr<Point<T>> c{nullptr};

        static void checkCorrect (Point<T> a, Point<T> b, Point<T> c) {
            double AB = (a - b).abs();
            double BC = (b - c).abs();
            double AC = (a - c).abs();

            bool sidesEq = Utils::cmpDouble(AB, BC) && Utils::cmpDouble(BC, AC);

            if (!sidesEq) {
                throw std::invalid_argument("Triangle sides must be equal.");
            }
        }

    protected:
        std::ostream& print (std::ostream& os) const override  {
            os << "Triangle (" << std::endl;
            os << "\tA = " << *a << std::endl;
            os << "\tB = " << *b << std::endl;
            os << "\tC = " << *c << std::endl;
            os << ")";
            return os;
        }

        std::istream& input (std::istream& is) override {
            Point<T> pA, pB, pC;

            std::cout << "Input Triangle (" << std::endl;

            std::cout << "Input point A = ";
            is >> pA;

            std::cout << "Input point B = ";
            is >> pB;

            std::cout << "Input point C = ";
            is >> pC;

            std::cout << ")" << std::endl;

            checkCorrect(pA, pB, pC);

            *a = pA;
            *b = pB;
            *c = pC;

            return is;
        }

    public:
        Triangle () {
            a = std::make_unique<Point<T>>(cos(0), sin(0));
            b = std::make_unique<Point<T>>(cos(M_PI / 3.0 * 2.0), sin(M_PI / 3.0 * 2.0));
            c = std::make_unique<Point<T>>(cos(M_PI / 3.0 * 4.0), sin(M_PI / 3.0 * 4.0));
        }

        Triangle (Point<T> pA, Point<T> pB, Point<T> pC) {
            checkCorrect(pA, pB, pC);
            a = std::make_unique<Point<T>>(pA);
            b = std::make_unique<Point<T>>(pB);
            c = std::make_unique<Point<T>>(pC);
        }

        Triangle (const Triangle<T> &other) {
            a = std::make_unique<Point<T>>(*other.a);
            b = std::make_unique<Point<T>>(*other.b);
            c = std::make_unique<Point<T>>(*other.c);
        }
        
        Triangle (Triangle<T> &&other) {
            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
        }

        Triangle<T>& operator= (const Triangle<T> &other) {
            if (this == &other) return *this;
            *a = *other.a;
            *b = *other.b;
            *c = *other.c;
            return *this;
        }

        Triangle<T>& operator= (Triangle<T> &&other) {
            a.reset();
            b.reset();
            c.reset();

            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);

            return *this;
        }        

        Point<T> calcRotationCenter () override {
            Point<T> mid = (*a + *b + *c) * (1.0 / 3.0);
            return mid;
        }

        operator double () override {
            double AB = (*a - *b).abs();
            double BC = (*b - *c).abs();
            double AC = (*a - *c).abs();
            return Utils::STriangle(AB, BC, AC);
        }

        std::unique_ptr<Array<Point<double>>> getPointsArray () override {
            std::unique_ptr<Array<Point<double>>> points = std::make_unique<Array<Point<double>>>();

            points->append(Point<double>(*a));
            points->append(Point<double>(*b));
            points->append(Point<double>(*c));

            return points;
        }

        bool operator== (const Triangle<T> &other) const {
            return *a == *other.a && *b == *other.b && *c == *other.c;
        }

        bool operator&& (const Triangle<T> &other) const {
            return Utils::cmpDouble((*a - *b).abs(), (*other.a - *other.b).abs());
        }

    friend std::ostream& operator<< (std::ostream& os, const Triangle<T> &triangle) {
        return triangle.print(os);
    }

    friend std::istream& operator>> (std::istream& is, Triangle<T> &triangle) {
        return triangle.input(is);
    }
};