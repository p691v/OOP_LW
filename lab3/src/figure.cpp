#include "../include/figure.h"

std::ostream& operator<< (std::ostream& os, const Figure &figure) {
    return figure.print(os);
}

std::istream& operator>> (std::istream& is, Figure &figure) {
    return figure.input(is);
}