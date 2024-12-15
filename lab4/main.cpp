#include <iostream>
#include <memory>

#include "include/custom-concepts.h"
#include "include/point.h"
#include "include/triangle.h"
#include "include/hexagon.h"
#include "include/octagon.h"
#include "include/array.h"
#include "include/figure.h"
using type = double;

std::shared_ptr<Figure<type>> get_figure() {
    int number = 0;
    std::cout << "Select figure you want to create:\nTriangle - 1\nRectangle - 2\nSquare - 3" << std::endl;
    std::cout << "Your input: ";
    std::cin >> number;
    switch (number) {
        case 1: {
            auto triangle = std::make_shared<Triangle<type>>();
            std::cin >> *triangle;
            return triangle;
        }
        case 2: {
            auto rectangle = std::make_shared<Hexagon<type>>();
            std::cin >> *rectangle;
            return rectangle;
        }
        case 3: {
            auto square = std::make_shared<Octagon<type>>();
            std::cin >> *square;
            return square;
        }
        default:
            std::cout << "Unknown figure number";
    }
    return nullptr;
}

void callBasicFunctions(std::shared_ptr<Array<Figure<type>>> array) {
    for (int i = 0; i < array->size; ++i) {
        auto figure = (*array)[i];
        std::cout << "Figure №" << i + 1 << std::endl;
        std::cout << "Center of figure:  " << figure.getCenter() << std::endl;
        std::cout << "Area of figure: " << static_cast<double> (figure) << std::endl;
    }
}

double total_area(std::shared_ptr<Array<Figure<type>>> array) {
    double res = 0.0;
    for (size_t i = 0; i != array->size; ++i) {
        res += static_cast<double> ((*array)[i]);
    }
    return res;
}


int call_function(int number, std::shared_ptr<Array<Figure<type>>> array) {
    switch (number) {
        case 1: {
            int index;
            if (array->getCapacity() == 0) {
                std::cout << "You have zero-length array" << std::endl;
                break;
            }
            auto figure = get_figure();
            if (figure != nullptr) {
                array->push_back(*figure);
            }
            break;
        }
        case 2:
            std::cout << "Getting center and area for every figure:" << std::endl;
            callBasicFunctions(array);
            break;
        case 3:
            std::cout << "Total area of all figures is: " << total_area(array) << std::endl;
            break;
        case 4:
            int index;
            std::cout << "Enter position in array to delete figure(starts from 0 till " << array->size - 1 << "): ";
            std::cin >> index;
            try {
                array->remove(index);
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
            break;
        case 5:
            return 0;
        default:
            break;
    }
    return 1;
}

int main() {
    int size;
    std::cout << "Enter size of figures array: ";
    std::cin >> size;
    auto array = std::make_shared<Array<Figure<type>>>(size);
    int number, status = 1;
    while (status) {
        std::cout
                << "Menu:\nNew figure - 1\nCall basic functions - 2\nCalculate total area - 3\nDelete figure by index - 4\nExit - 5"
                << std::endl;
        std::cout << "Enter command number: ";
        std::cin >> number;
        status = call_function(number, array);
    }
}