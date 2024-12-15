#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "utils.h"
#include "custom-concepts.h"

template <Arithmetic T>
class Point {
    private:
        T x;
        T y;

    public:
        Point () : x{0}, y{0} {}
        Point (T xValue, T yValue) : x{xValue}, y{yValue} {}
        Point (T value) : Point(value, value) {}
        Point (const Point<T> &other) : Point(other.x, other.y) {}

        template <class TOther>
        Point (const Point<TOther> &other) : Point(static_cast<T>(other.x), static_cast<T>(other.x)) {}

        Point (Point<T> &&other) {
            std::swap(x, other.x);
            std::swap(y, other.y);
        }

        Point<T>& operator= (const Point<T> &other) {
            if (this == &other) return *this;
            x = other.x;
            y = other.y;
            return *this; 
        }

        Point<T>& operator= (Point<T> &&other) {
            std::swap(x, other.x);
            std::swap(y, other.y);
            return *this;
        }

        bool operator== (const Point<T> &other) const {
            return Utils::cmpDouble(x, other.x) && Utils::cmpDouble(y, other.y);
        }

        Point<T> operator+ (const Point<T> &other) const {
            return Point(x + other.x, y + other.y);
        }

        Point<T> operator- (const Point<T> &other) const {
            return Point(x - other.x, y - other.y);
        }

        Point<T> operator* (T number) const {
            return Point(number * x, number * y);
        }

        double abs () const {
            return sqrt(x * x + y * y);
        }

        T getX () const {
            return x;
        }

        T getY () const {
            return y;
        }

        void setX (T xValue) {
            x = xValue;
        }

        void setY (T yValue) {
            y = yValue;
        }

    friend std::ostream& operator<< (std::ostream& os, const Point<T> &point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }

    friend std::istream& operator>> (std::istream& is, Point<T> &point) {
        T x, y;

        std::cout << "(" << std::endl << "\tInput x for point: ";
        is >> x;
        std::cout << "\tInput y for point: ";
        is >> y;
        std::cout << ")" << std::endl;

        point.x = x;
        point.y = y;

        return is;
    }
};
