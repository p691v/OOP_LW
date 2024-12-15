#include <gtest/gtest.h>
#include <math.h>
#include <stdexcept>

#include "../include/utils.h"
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/triangle.h"
#include "../include/hexagon.h"
#include "../include/octagon.h"
#include "../include/array.h"

TEST(utils, cmp_double_eq) {
    double a = 0.1 + 0.2;
    double b = 0.3;
    bool result = Utils::cmpDouble(a, b);
    
    ASSERT_TRUE(result == true);
}

TEST(utils, cmp_double_not_eq) {
    double a = 0.1 + 0.2;
    double b = 0.31;
    bool result = Utils::cmpDouble(a, b);
    
    ASSERT_TRUE(result == false);
}

TEST(point, getter_x) {
    Point point(2.0, 3.0);
    double getXRes = point.getX();

    ASSERT_TRUE(getXRes == 2.0);
}

TEST(point, getter_y) {
    Point point(2.0, 3.0);
    double getYRes = point.getY();

    ASSERT_TRUE(getYRes == 3.0);
}

TEST(point, cmp_eq) {
    Point a(0.0, 3.0);
    Point b(0.0, 1.0 + 2.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == true);
}

TEST(point, cmp_not_eq_x) {
    Point a(0.0, 3.0);
    Point b(1.0, 3.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == false);
}

TEST(point, cmp_not_eq_y) {
    Point a(0.0, 3.0);
    Point b(0.0, -1.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == false);
}

TEST(point, cmp_not_eq_x_y) {
    Point a(0.0, 3.0);
    Point b(2.0, -1.0);
    bool abEq = a == b;

    ASSERT_TRUE(abEq == false);
}

TEST(point, default_constructor) {
    Point<double> point;
    Point pointRef(0.0, 0.0);
    bool result = point == pointRef; 

    ASSERT_TRUE(result == true);
}

TEST(point, single_number_constructor) {
    Point point(1.0);
    Point pointRef(1.0, 1.0);
    bool result = point == pointRef; 

    ASSERT_TRUE(result == true);
}

TEST(point, copy) {
    Point pointSrc(1.0, 2.0);
    Point point{pointSrc};
    bool result = point == pointSrc; 

    ASSERT_TRUE(result == true);
}

TEST(point, assigment) {
    Point pointSrc(1.0, 2.0);
    Point point = pointSrc;
    bool result = point == pointSrc; 

    ASSERT_TRUE(result == true);
}

TEST(point, sum) {
    Point a(1.0, 2.2);
    Point b(3.0, -8.5);
    Point sumRef(4.0, -6.3);
    Point sum = a + b;

    ASSERT_TRUE(sum == sumRef);
}

TEST(point, diff) {
    Point a(1.0, 2.2);
    Point b(3.0, -8.5);
    Point diffRef(-2.0, 10.7);
    Point diff = a - b;

    ASSERT_TRUE(diff == diffRef);
}

TEST(point, product) {
    Point a(1.5, -2.2);
    double k = -2.0;
    Point productRef(-3.0, 4.4);
    Point product = a * k;

    ASSERT_TRUE(product == productRef);
}

TEST(point, abs) {
    Point a(3.0, -4.0);
    double absRef = 5.0;
    double abs = a.abs();

    ASSERT_TRUE(Utils::cmpDouble(absRef, abs));
}

TEST(triangle, default_constructor) {
    Triangle<double> tr;
    Triangle trRef(
        Point(cos(0.0), sin(0.0)),
        Point(cos(M_PI / 3.0 * 2.0), sin(M_PI / 3.0 * 2.0)),
        Point(cos(M_PI / 3.0 * 4.0), sin(M_PI / 3.0 * 4.0))
    );
    bool result = tr == trRef;

    ASSERT_TRUE(result == true);
}

TEST(triangle, invalid_arguments_1) {
    EXPECT_THROW(Triangle tr(
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 0.0)
    ), std::invalid_argument);
}

TEST(triangle, invalid_arguments_2) {
    EXPECT_THROW(Triangle tr(
        Point(0.0),
        Point(1.0),
        Point(2.0)
    ), std::invalid_argument);
}

TEST(triangle, copy) {
    Triangle trSrc(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );
    Triangle tr{trSrc};
    bool result = tr == trSrc; 

    ASSERT_TRUE(result == true);
}

TEST(triangle, assigment) {
    Triangle trSrc(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );
    Triangle tr = trSrc;
    bool result = tr == trSrc; 

    ASSERT_TRUE(result == true);
}

TEST(triangle, rotation_center) {
    Triangle tr(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );
    Point rotCenterRef(1.0, 1.7320508 / 3.0);
    Point rotCenter = tr.calcRotationCenter();

    ASSERT_TRUE(rotCenter == rotCenterRef);
}

TEST(triangle, area) {
    Triangle tr(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );
    double areaRef = 0.5 * 2.0 * 2.0 * sin(M_PI / 3.0);
    double area = static_cast<double>(tr);
    
    ASSERT_TRUE(Utils::cmpDouble(area, areaRef));
}

TEST(triangle, geometric_equivalence) {
    Triangle tr1(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );

    Triangle tr2(
        Point(0.0 + 2.0, 0.0),
        Point(1.5 + 0.5 + 2.0, 0.0),
        Point(1.0 + 2.0, - 1.0 - 0.7320508)
    );

    bool result = tr1 && tr2;

    ASSERT_TRUE(result == true);
}

TEST(triangle, cmp_eq) {
    Triangle tr1(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );

    Triangle tr2(
        Point(0.0),
        Point(1.5 + 0.5, 0.0),
        Point(1.0, 1.7320508)
    );

    bool result = tr1 == tr2;

    ASSERT_TRUE(result == true);
}

TEST(triangle, cmp_not_eq) {
    Triangle tr1(
        Point(0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.7320508)
    );

    Triangle tr2(
        Point(0.0),
        Point(1.5 + 0.5, 0.0),
        Point(1.0, - 1.0 - 0.7320508)
    );

    bool result = tr1 == tr2;

    ASSERT_TRUE(result == false);
}

// шестиугольник

TEST(hexagon, default_constructor) {
    Hexagon<double> tr;
    Hexagon<double> trRef(
        Point(cos(0.0), sin(0.0)),
        Point(cos(M_PI / 3.0), sin(M_PI / 3.0)),
        Point(cos(M_PI * 2.0 / 3.0), sin(M_PI * 2.0 / 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI * 4.0 / 3.0), sin(M_PI * 4.0 / 3.0)),
        Point(cos(M_PI * 5.0 / 3.0), sin(M_PI * 5.0 / 3.0))
    );
    bool result = tr == trRef;

    ASSERT_TRUE(result == true);
}

TEST(hexagon, invalid_arguments_same_points) {
    EXPECT_THROW(Hexagon fig(
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0)
    ), std::invalid_argument);
}

TEST(hexagon, invalid_arguments_not_regular) {
    EXPECT_THROW(Hexagon fig(
        Point(0.0),
        Point(1.0, 0.0),
        Point(1.0),
        Point(2.0, 1.0),
        Point(2.0, 0.0),
        Point(1.0, 0.0)
    ), std::invalid_argument);
}

TEST(hexagon, copy) {
    Hexagon trSrc(
        Point(cos(M_PI / 3.0), sin(M_PI / 3.0)),
        Point(cos(M_PI * 2.0 / 3.0), sin(M_PI * 2.0 / 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI * 4.0 / 3.0), sin(M_PI * 4.0 / 3.0)),
        Point(cos(M_PI * 5.0 / 3.0), sin(M_PI * 5.0 / 3.0)),
        Point(cos(0.0), sin(0.0))
    );
    Hexagon tr{trSrc};
    bool result = tr == trSrc; 

    ASSERT_TRUE(result == true);
}

TEST(hexagon, assigment) {
    Hexagon trSrc(
        Point(cos(M_PI / 3.0), sin(M_PI / 3.0)),
        Point(cos(M_PI * 2.0 / 3.0), sin(M_PI * 2.0 / 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI * 4.0 / 3.0), sin(M_PI * 4.0 / 3.0)),
        Point(cos(M_PI * 5.0 / 3.0), sin(M_PI * 5.0 / 3.0)),
        Point(cos(0.0), sin(0.0))
    );
    Hexagon tr = trSrc;
    bool result = tr == trSrc; 

    ASSERT_TRUE(result == true);
}

TEST(hexagon, rotation_center) {
    Hexagon tr(
        Point(2.0 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 3.5 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0)),
        Point(2.0 + cos(0.0), 3.5 + sin(0.0))
    );
    Point rotCenterRef(2.0, 3.5);
    Point rotCenter = tr.calcRotationCenter();

    ASSERT_TRUE(rotCenter == rotCenterRef);
}

TEST(hexagon, area) {
    Hexagon tr(
        Point(2.0 * cos(M_PI / 3.0), 2.0 * sin(M_PI / 3.0)),
        Point(2.0 * cos(M_PI * 2.0 / 3.0), 2.0 * sin(M_PI * 2.0 / 3.0)),
        Point(2.0 * cos(M_PI), 2.0 * sin(M_PI)),
        Point(2.0 * cos(M_PI * 4.0 / 3.0), 2.0 * sin(M_PI * 4.0 / 3.0)),
        Point(2.0 * cos(M_PI * 5.0 / 3.0), 2.0 * sin(M_PI * 5.0 / 3.0)),
        Point(2.0 * cos(0.0), 2.0 * sin(0.0))
    );
    double areaRef = 0.5 * 2.0 * 2.0 * sin(M_PI / 3.0) * 6.0;
    double area = static_cast<double>(tr);
    
    ASSERT_TRUE(Utils::cmpDouble(area, areaRef));
}

TEST(hexagon, geometric_equivalence) {
    Hexagon tr1(
        Point(2.0 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 3.5 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0)),
        Point(2.0 + cos(0.0), 3.5 + sin(0.0))
    );

    Hexagon tr2(
        Point(1.5 + 0.5 + cos(0.0), 3.5 + sin(0.0)),
        Point(2.0 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 4.5 - 1.0 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0))
    );

    bool result = tr1 && tr2;

    ASSERT_TRUE(result == true);
}

TEST(hexagon, cmp_eq) {
    Hexagon tr1(
        Point(2.0 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 3.5 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0)),
        Point(2.0 + cos(0.0), 3.5 + sin(0.0))
    );

    Hexagon tr2(
        Point(1.5 + 0.5 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 3.5 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0)),
        Point(2.0 + cos(0.0), 3.5 + sin(0.0))
    );

    bool result = tr1 == tr2;

    ASSERT_TRUE(result == true);
}

TEST(hexagon, cmp_not_eq) {
    Hexagon tr1(
        Point(2.0 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 3.5 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0)),
        Point(2.0 + cos(0.0), 3.5 + sin(0.0))
    );

    Hexagon tr2(
        Point(1.5 + 0.5 + cos(0.0), 3.5 + sin(0.0)),
        Point(2.0 + cos(M_PI / 3.0), 3.5 + sin(M_PI / 3.0)),
        Point(2.0 + cos(M_PI * 2.0 / 3.0), 3.5 + sin(M_PI * 2.0 / 3.0)),
        Point(2.0 + cos(M_PI), 4.5 - 1.0 + sin(M_PI)),
        Point(2.0 + cos(M_PI * 4.0 / 3.0), 3.5 + sin(M_PI * 4.0 / 3.0)),
        Point(2.0 + cos(M_PI * 5.0 / 3.0), 3.5 + sin(M_PI * 5.0 / 3.0))
    );

    bool result = tr1 == tr2;

    ASSERT_TRUE(result == false);
}

// восьмиугольник
TEST(octagon, default_constructor) {
    Octagon<double> tr;
    Octagon trRef(
        Point(cos(0.0), sin(0.0)),
        Point(cos(M_PI / 4.0), sin(M_PI / 4.0)),
        Point(cos(M_PI / 2.0), sin(M_PI / 2.0)),
        Point(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0)),
        Point(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0)),
        Point(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0))
    );
    bool result = tr == trRef;

    ASSERT_TRUE(result == true);
}

TEST(octagon, invalid_arguments_same_points) {
    EXPECT_THROW(Octagon fig(
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0),
        Point(1.0, 0.0)
    ), std::invalid_argument);
}

TEST(octagon, invalid_arguments_not_regular) {
    EXPECT_THROW(Octagon fig(
        Point(0.0),
        Point(1.0, 0.0),
        Point(1.0),
        Point(2.0, 1.0),
        Point(3.0, 1.0),
        Point(3.0, 0.0),
        Point(2.0, 0.0),
        Point(1.0, 0.0)
    ), std::invalid_argument);
}

TEST(octagon, copy) {
    Octagon trSrc(
        Point(cos(M_PI / 4.0), sin(M_PI / 4.0)),
        Point(cos(M_PI / 2.0), sin(M_PI / 2.0)),
        Point(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0)),
        Point(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0)),
        Point(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0)),
        Point(cos(0.0), sin(0.0))
    );
    Octagon tr{trSrc};
    bool result = tr == trSrc; 

    ASSERT_TRUE(result == true);
}

TEST(octagon, assigment) {
    Octagon trSrc(
        Point(cos(M_PI / 4.0), sin(M_PI / 4.0)),
        Point(cos(M_PI / 2.0), sin(M_PI / 2.0)),
        Point(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0)),
        Point(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0)),
        Point(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0)),
        Point(cos(0.0), sin(0.0))
    );
    Octagon tr = trSrc;
    bool result = tr == trSrc; 

    ASSERT_TRUE(result == true);
}

TEST(octagon, rotation_center) {
    Octagon tr(
        Point(-4.5 + cos(M_PI / 4.0), 5.0 + sin(M_PI / 4.0)),
        Point(-4.5 + cos(M_PI / 2.0), 5.0 + sin(M_PI / 2.0)),
        Point(-4.5 + cos(M_PI / 4.0 * 3.0), 5.0 + sin(M_PI / 4.0 * 3.0)),
        Point(-4.5 + cos(M_PI), 5.0 + sin(M_PI)),
        Point(-4.5 + cos(M_PI / 4.0 * 5.0), 5.0 + sin(M_PI / 4.0 * 5.0)),
        Point(-4.5 + cos(M_PI / 2.0 * 3.0), 5.0 + sin(M_PI / 2.0 * 3.0)),
        Point(-4.5 + cos(M_PI / 4.0 * 7.0), 5.0 + sin(M_PI / 4.0 * 7.0)),
        Point(-4.5 + cos(0.0), 5.0 + sin(0.0))
    );
    Point rotCenterRef(-4.5, 5.0);
    Point rotCenter = tr.calcRotationCenter();

    ASSERT_TRUE(rotCenter == rotCenterRef);
}

TEST(octagon, area) {
    Octagon tr(
        Point(2.0 * cos(0.0), 2.0 * sin(0.0)),
        Point(2.0 * cos(M_PI / 4.0), 2.0 * sin(M_PI / 4.0)),
        Point(2.0 * cos(M_PI / 2.0), 2.0 * sin(M_PI / 2.0)),
        Point(2.0 * cos(M_PI / 4.0 * 3.0), 2.0 * sin(M_PI / 4.0 * 3.0)),
        Point(2.0 * cos(M_PI), 2.0 * sin(M_PI)),
        Point(2.0 * cos(M_PI / 4.0 * 5.0), 2.0 * sin(M_PI / 4.0 * 5.0)),
        Point(2.0 * cos(M_PI / 2.0 * 3.0), 2.0 * sin(M_PI / 2.0 * 3.0)),
        Point(2.0 * cos(M_PI / 4.0 * 7.0), 2.0 * sin(M_PI / 4.0 * 7.0))
    );
    double areaRef = 0.5 * 2.0 * 2.0 * sin(M_PI / 4.0) * 8.0;
    double area = static_cast<double>(tr);
    
    ASSERT_TRUE(Utils::cmpDouble(area, areaRef));
}
 
TEST(octagon, geometric_equivalence) {
    Octagon tr1(
        Point(-4.5 - cos(M_PI / 4.0), 5.0 + sin(M_PI / 4.0)),
        Point(-4.5 - cos(M_PI / 2.0), 5.0 + sin(M_PI / 2.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 3.0), 5.0 + sin(M_PI / 4.0 * 3.0)),
        Point(-4.5 - cos(M_PI), 5.0 + sin(M_PI)),
        Point(-4.5 - cos(M_PI / 4.0 * 5.0), 5.0 + sin(M_PI / 4.0 * 5.0)),
        Point(-4.5 - cos(M_PI / 2.0 * 3.0), 5.0 + sin(M_PI / 2.0 * 3.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 7.0), 5.0 + sin(M_PI / 4.0 * 7.0)),
        Point(-4.5 - cos(0.0), 5.0 + sin(0.0))
    );

    Octagon tr2(
        Point(cos(M_PI / 4.0), sin(M_PI / 4.0)),
        Point(cos(M_PI / 2.0), sin(M_PI / 2.0)),
        Point(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0)),
        Point(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0)),
        Point(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0)),
        Point(cos(0.0), sin(0.0))
    );

    bool result = tr1 && tr2;

    ASSERT_TRUE(result == true);
}

TEST(octagon, cmp_eq) {
    Octagon tr1(
        Point(-4.5 - cos(M_PI / 4.0), 5.0 + sin(M_PI / 4.0)),
        Point(-4.5 - cos(M_PI / 2.0), 5.0 + sin(M_PI / 2.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 3.0), 5.0 + sin(M_PI / 4.0 * 3.0)),
        Point(-4.5 - cos(M_PI), 5.0 + sin(M_PI)),
        Point(-4.5 - cos(M_PI / 4.0 * 5.0), 5.0 + sin(M_PI / 4.0 * 5.0)),
        Point(-4.5 - cos(M_PI / 2.0 * 3.0), 5.0 + sin(M_PI / 2.0 * 3.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 7.0), 5.0 + sin(M_PI / 4.0 * 7.0)),
        Point(-4.5 - cos(0.0), 5.0 + sin(0.0))
    );

    Octagon tr2(
        Point(-4.5 - cos(M_PI / 4.0), 2.7 + 2.3 + sin(M_PI / 4.0)),
        Point(-4.5 - cos(M_PI / 2.0), 5.0 + sin(M_PI / 2.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 3.0), 5.0 + sin(M_PI / 4.0 * 3.0)),
        Point(-4.5 - cos(M_PI), 5.0 + sin(M_PI)),
        Point(-4.5 - cos(M_PI / 4.0 * 5.0), 5.0 + sin(M_PI / 4.0 * 5.0)),
        Point(-4.5 - cos(M_PI / 2.0 * 3.0), 5.0 + sin(M_PI / 2.0 * 3.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 7.0), 5.0 + sin(M_PI / 4.0 * 7.0)),
        Point(-4.5 - cos(0.0), 5.0 + sin(0.0))
    );

    bool result = tr1 == tr2;

    ASSERT_TRUE(result == true);
}

TEST(octagon, cmp_not_eq) {
    Octagon tr1(
        Point(-4.5 - cos(M_PI / 4.0), 5.0 + sin(M_PI / 4.0)),
        Point(-4.5 - cos(M_PI / 2.0), 5.0 + sin(M_PI / 2.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 3.0), 5.0 + sin(M_PI / 4.0 * 3.0)),
        Point(-4.5 - cos(M_PI), 5.0 + sin(M_PI)),
        Point(-4.5 - cos(M_PI / 4.0 * 5.0), 5.0 + sin(M_PI / 4.0 * 5.0)),
        Point(-4.5 - cos(M_PI / 2.0 * 3.0), 5.0 + sin(M_PI / 2.0 * 3.0)),
        Point(-4.5 - cos(M_PI / 4.0 * 7.0), 5.0 + sin(M_PI / 4.0 * 7.0)),
        Point(-4.5 - cos(0.0), 5.0 + sin(0.0))
    );

    Octagon tr2(
        Point(cos(M_PI / 4.0), sin(M_PI / 4.0)),
        Point(cos(M_PI / 2.0), sin(M_PI / 2.0)),
        Point(cos(M_PI / 4.0 * 3.0), sin(M_PI / 4.0 * 3.0)),
        Point(cos(M_PI), sin(M_PI)),
        Point(cos(M_PI / 4.0 * 5.0), sin(M_PI / 4.0 * 5.0)),
        Point(cos(M_PI / 2.0 * 3.0), sin(M_PI / 2.0 * 3.0)),
        Point(cos(M_PI / 4.0 * 7.0), sin(M_PI / 4.0 * 7.0)),
        Point(cos(0.0), sin(0.0))
    );

    bool result = tr1 == tr2;

    ASSERT_TRUE(result == false);
}

TEST(array, default_constructor) {
    Array<int> array;
    int result = array.getSize();

    ASSERT_TRUE(result == 0);
}

TEST(array, append) {
    Array<int> array;
    array.append(0);
    int firstElem = array[0];
    int length = array.getSize();

    ASSERT_TRUE(firstElem == 0 && length == 1);
}

TEST(array, extend) {
    const int countToAdd = 100;

    Array<int> array;
    
    ASSERT_NO_THROW({
        for (int i = 0; i < countToAdd; i++) {
            array.append(i);
        }
    });

    int length = array.getSize();

    ASSERT_TRUE(length == countToAdd);
}

TEST(array, delete_on_index) {
    Array<int> array;

    array.append(1);
    array.append(2);
    array.append(3);

    array.deleteOnIndex(1);

    int firstElem = array[0];
    int secondElem = array[1];
    int length = array.getSize();

    ASSERT_TRUE(firstElem == 1 && secondElem == 3 && length == 2);
}

TEST(array, delete_on_index_last) {
    Array<int> array;

    array.append(1);
    array.append(2);

    array.deleteOnIndex(1);

    int firstElem = array[0];
    int length = array.getSize();

    ASSERT_TRUE(firstElem == 1 && length == 1);
}

TEST(array, copy) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> copyArray{array};

    int firstElem = copyArray[0];
    int secondElem = copyArray[1];
    int length = copyArray.getSize();

    int firstElemSrc = array[0];
    int secondElemSrc = array[1];
    int lengthSrc = array.getSize();    

    ASSERT_TRUE(firstElem == 1 && secondElem == 2 && length == 2); 
    ASSERT_TRUE(firstElemSrc == 1 && secondElemSrc == 2 && lengthSrc == 2);
}

TEST(array, move) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> copyArray{std::move(array)};

    int firstElem = copyArray[0];
    int secondElem = copyArray[1];
    int length = copyArray.getSize();
    int lengthSrc = array.getSize();    

    ASSERT_TRUE(firstElem == 1 && secondElem == 2 && length == 2 && lengthSrc == 0); 
}

TEST(array, assigment) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> copyArray = array;

    int firstElem = copyArray[0];
    int secondElem = copyArray[1];
    int length = copyArray.getSize();

    int firstElemSrc = array[0];
    int secondElemSrc = array[1];
    int lengthSrc = array.getSize();    

    ASSERT_TRUE(firstElem == 1 && secondElem == 2 && length == 2); 
    ASSERT_TRUE(firstElemSrc == 1 && secondElemSrc == 2 && lengthSrc == 2);
}

TEST(array, assigment_move) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> copyArray = std::move(array);

    int firstElem = copyArray[0];
    int secondElem = copyArray[1];
    int length = copyArray.getSize();
    int lengthSrc = array.getSize();    

    ASSERT_TRUE(firstElem == 1 && secondElem == 2 && length == 2 && lengthSrc == 0); 
}

TEST(array, pointer_destruction) {
    struct A {
        bool *flagAddr;

        A (bool *addr) : flagAddr{addr} {}

        ~A () {
            *flagAddr = true;
        }
    };   

    bool destructed = false;

    {
        Array<A*> array;
        array.append(new A(&destructed));
    }

    ASSERT_TRUE(destructed);
}

TEST(array, cmp_equal) {
    Array<int> array;

    array.append(1);
    array.append(2);

    Array<int> array2;

    array2.append(1);
    array2.append(2);

    bool result = array == array2;

    ASSERT_TRUE(result == true);
}

TEST(array, cmp_not_equal_elem) {
    Array<int> array;

    array.append(1);
    array.append(3);
    array.append(3);

    Array<int> array2;

    array2.append(1);
    array2.append(2);
    array2.append(3);

    bool result = array == array2;

    ASSERT_TRUE(result == false);
}

TEST(array, cmp_not_equal_length) {
    Array<int> array;

    array.append(1);
    array.append(2);
    array.append(3);

    Array<int> array2;

    array2.append(1);
    array2.append(2);

    bool result = array == array2;

    ASSERT_TRUE(result == false);
}

TEST(array, concat) {
    Array<int> array1;
    
    array1.append(1);
    array1.append(2);
    array1.append(3);
    
    Array<int> array2;
    
    array2.append(4);
    array2.append(5);

    array1.append(array2);

    Array<int> arrayRef;

    arrayRef.append(1);
    arrayRef.append(2);
    arrayRef.append(3);
    arrayRef.append(4);
    arrayRef.append(5);

    ASSERT_TRUE(array1 == arrayRef);
}

int main (int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}