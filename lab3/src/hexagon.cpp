#include "../include/hexagon.h"

void Hexagon::checkCorrect (Point a, Point b, Point c, Point d, Point e, Point f) {
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

Hexagon::Hexagon () {
    a = Point(cos(0.0), sin(0.0));
    b = Point(cos(M_PI / 3.0), sin(M_PI / 3.0));
    c = Point(cos(M_PI * 2.0 / 3.0), sin(M_PI * 2.0 / 3.0));
    d = Point(cos(M_PI), sin(M_PI));
    e = Point(cos(M_PI * 4.0 / 3.0), sin(M_PI * 4.0 / 3.0));
    f = Point(cos(M_PI * 5.0 / 3.0), sin(M_PI * 5.0 / 3.0));
}

Hexagon::Hexagon (Point pA, Point pB, Point pC, Point pD, Point pE, Point pF) {
    checkCorrect(pA, pB, pC, pD, pE, pF);

    a = pA;
    b = pB;
    c = pC;
    d = pD;
    e = pE;
    f = pF;
}

Hexagon::Hexagon (const Hexagon &other) : a{other.a}, b{other.b}, c{other.c}, d{other.d}, e{other.e}, f{other.f} {}

Hexagon::Hexagon (Hexagon &&other) {
    std::swap(a, other.a);
    std::swap(b, other.b);
    std::swap(c, other.c);
    std::swap(d, other.d);
    std::swap(e, other.e);
    std::swap(f, other.f);
}

Hexagon& Hexagon::operator= (const Hexagon &other) {
    if (this == &other) return *this;
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    e = other.e;
    f = other.f;
    return *this;
}

Hexagon& Hexagon::operator= (Hexagon &&other) {
    std::swap(a, other.a);
    std::swap(b, other.b);
    std::swap(c, other.c);
    std::swap(d, other.d);
    std::swap(e, other.e);
    std::swap(f, other.f);
    return *this;
}

Point Hexagon::calcRotationCenter () {
    Point mid = (a + b + c + d + e + f) * (1.0 / 6.0);
    return mid;
}

Hexagon::operator double () {
    return (a - b).abs() * sin(M_PI / 3) * 6.0;
}

bool Hexagon::operator== (const Hexagon &other) const {
    return a == other.a && b == other.b && c == other.c && d == other.d && e == other.e && f == other.f;
}   

bool Hexagon::operator&& (const Hexagon &other) const {
    return Utils::cmpDouble((a - b).abs(), (other.a - other.b).abs());
}

std::ostream& Hexagon::print (std::ostream& os) const {
    os << "Hexagon (" << std::endl;
    os << "\tA = " << a << std::endl;
    os << "\tB = " << b << std::endl;
    os << "\tC = " << c << std::endl;
    os << "\tD = " << d << std::endl;
    os << "\tE = " << e << std::endl;
    os << "\tF = " << f << std::endl;
    os << ")";
    return os;
}

std::istream& Hexagon::input (std::istream& is) {
    Point pA, pB, pC, pD, pE, pF;

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

    a = pA;
    b = pB;
    c = pC;
    d = pD;
    e = pE;
    f = pF;

    return is;
}

std::ostream& operator<< (std::ostream& os, const Hexagon &hexagon) {
    return hexagon.print(os);
}

std::istream& operator>> (std::istream& is, Hexagon &hexagon) {
    return hexagon.input(is);
}
