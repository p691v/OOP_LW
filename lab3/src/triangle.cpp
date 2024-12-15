#include "../include/triangle.h"

void Triangle::validate (Point a, Point b, Point c) {
    double AB = (a - b).abs();
    double BC = (b - c).abs();
    double AC = (a - c).abs();

    bool sidesEq = Utils::cmpDouble(AB, BC) && Utils::cmpDouble(BC, AC);

    if (!sidesEq) {
        throw std::invalid_argument("Triangle sides must be equal.");
    }
}

Triangle::Triangle () {
    a = Point(cos(0), sin(0));
    b = Point(cos(M_PI / 3.0 * 2.0), sin(M_PI / 3.0 * 2.0));
    c = Point(cos(M_PI / 3.0 * 4.0), sin(M_PI / 3.0 * 4.0));
}

Triangle::Triangle (Point pA, Point pB, Point pC) {
    validate(pA, pB, pC);
    a = pA;
    b = pB;
    c = pC;
}

Triangle::Triangle (const Triangle &other) : a{other.a}, b{other.b}, c{other.c} {}

Triangle::Triangle (Triangle &&other) {
    std::swap(a, other.a);
    std::swap(b, other.b);
    std::swap(c, other.c);
}

Triangle& Triangle::operator= (const Triangle &other) {
    if (this == &other) return *this;
    a = other.a;
    b = other.b;
    c = other.c;
    return *this;
}

Triangle& Triangle::operator= (Triangle &&other) {
    std::swap(a, other.a);
    std::swap(b, other.b);
    std::swap(c, other.c);
    return *this;
}

Point Triangle::calcRotationCenter () {
    Point mid = (a + b + c) * (1.0 / 3.0);
    return mid;
}

Triangle::operator double () {
    double AB = (a - b).abs();
    double BC = (b - c).abs();
    double AC = (a - c).abs();
    return Utils::triangleArea(AB, BC, AC);
}

bool Triangle::operator== (const Triangle &other) const {
    return a == other.a && b == other.b && c == other.c;
}

bool Triangle::operator&& (const Triangle &other) const {
    return Utils::cmpDouble((a - b).abs(), (other.a - other.b).abs());
}

std::ostream& Triangle::print (std::ostream& os) const {
    os << "Triangle (" << std::endl;
    os << "\tA = " << a << std::endl;
    os << "\tB = " << b << std::endl;
    os << "\tC = " << c << std::endl;
    os << ")";
    return os;
}

std::istream& Triangle::input (std::istream& is) {
    Point pA, pB, pC;

    std::cout << "Input Triangle (" << std::endl;

    std::cout << "Input point A = ";
    is >> pA;

    std::cout << "Input point B = ";
    is >> pB;

    std::cout << "Input point C = ";
    is >> pC;

    std::cout << ")" << std::endl;

    validate(pA, pB, pC);

    a = pA;
    b = pB;
    c = pC;

    return is;
}

std::ostream& operator<< (std::ostream& os, const Triangle &triangle) {
    return triangle.print(os);
}

std::istream& operator>> (std::istream& is, Triangle &triangle) {
    return triangle.input(is);
}
