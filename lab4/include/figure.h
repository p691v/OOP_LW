#pragma once
#include <iostream>
#include <fstream>
#include "point.h"
#include "custom-concepts.h"
#include "array.h"

template <Arithmetic T>
class Figure {
    public:
        virtual Point<T> calcRotationCenter () = 0;
        virtual operator double() = 0;
        virtual std::unique_ptr<Array<Point<double>>> getPointsArray () = 0; 

        virtual ~Figure () = default;

    protected:
        virtual std::ostream& print (std::ostream& os) const = 0;
        virtual std::istream& input (std::istream& is) = 0;

    friend std::ostream& operator<< (std::ostream& os, const Figure<T> &figure) {
        return figure.print(os);
    }

    friend std::istream& operator>> (std::istream& is, Figure<T> &figure) {
        return figure.input(is);
    }
};