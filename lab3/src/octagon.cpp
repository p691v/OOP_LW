#include "../include/octagon.h"

void Octagon::checkCorrect (Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h) {
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
        throw std::invalid_argument("Invalid points for a regular octagon.");
    }
}

Octagon::Octagon () {
    a = Point(cos(0.0), sin(0.0));
    b = Point(cos(M_PI / 4.0), sin(M_PI / 4.0));
    c = Point(cos(M_PI / 2.0), sin(M_PI / 2.0));
    d = Point(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0));
    e = Point(cos(M_PI), sin(M_PI));
    f = Point(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0));
    g = Point(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0));
    h = Point(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0));    
}

Octagon::Octagon (Point pA, Point pB, Point pC, Point pD, Point pE, Point pF, Point pG, Point pH) {
    checkCorrect(pA, pB, pC, pD, pE, pF, pG, pH);

    a = pA;
    b = pB;
    c = pC;
    d = pD;
    e = pE;
    f = pF;
    g = pG;
    h = pH;
}

Octagon::Octagon (const Octagon &other) {
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    e = other.e;
    f = other.f;
    g = other.g;
    h = other.h;
}

Octagon::Octagon (Octagon &&other) {
    std::swap(a, other.a);
    std::swap(b, other.b);
    std::swap(c, other.c);
    std::swap(d, other.d);
    std::swap(e, other.e);
    std::swap(f, other.f);
    std::swap(g, other.g);
    std::swap(h, other.h);
}

Octagon& Octagon::operator= (const Octagon &other) {
    if (this == &other) return *this;
    a = other.a;
    b = other.b;
    c = other.c;
    d = other.d;
    e = other.e;
    f = other.f;
    g = other.g;
    h = other.h;
    return *this;
}

Octagon& Octagon::operator= (Octagon &&other) {
    std::swap(a, other.a);
    std::swap(b, other.b);
    std::swap(c, other.c);
    std::swap(d, other.d);
    std::swap(e, other.e);
    std::swap(f, other.f);
    std::swap(g, other.g);
    std::swap(h, other.h);
    return *this;
}

Point Octagon::calcRotationCenter () {
    Point mid = (a + b + c + d + e + f + g + h) * (1.0 / 8.0);
    return mid;
}

Octagon::operator double () {
    return (a - e).abs() * sin(M_PI / 4.0) * 4.0;
}

bool Octagon::operator== (const Octagon &other) const {
    return a == other.a && b == other.b && c == other.c && d == other.d && 
        e == other.e && f == other.f && g == other.g && h == other.h; 
}

bool Octagon::operator&& (const Octagon &other) const {
    return Utils::cmpDouble((a - b).abs(), (other.a - other.b).abs());
}

std::ostream& Octagon::print (std::ostream& os) const {
    os << "Octagon (" << std::endl;
    os << "\tA = " << a << std::endl;
    os << "\tB = " << b << std::endl;
    os << "\tC = " << c << std::endl;
    os << "\tD = " << d << std::endl;
    os << "\tE = " << e << std::endl;
    os << "\tF = " << f << std::endl;
    os << "\tG = " << g << std::endl;
    os << "\tH = " << h << std::endl;
    os << ")";
    return os;
}

std::istream& Octagon::input (std::istream& is) {
    Point pA, pB, pC, pD, pE, pF, pG, pH;

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

    a = pA;
    b = pB;
    c = pC;
    d = pD;
    e = pE;
    f = pF;
    g = pG;
    h = pH;

    return is;
}

std::ostream& operator<< (std::ostream& os, const Octagon &octagon) {
    return octagon.print(os);
}

std::istream& operator>> (std::istream& is, Octagon &octagon) {
    return octagon.input(is);
}
