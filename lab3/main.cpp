#include <iostream>

#include "include/point.h"
#include "include/figure.h"
#include "include/triangle.h"
#include "include/hexagon.h"
#include "include/octagon.h"

void addFigure (Figure **figures, int &size, const int &capacity);
void deleteFigure (Figure **figures, int &size, const int &capacity);
void printInfo (Figure **figures, int &size, const int &capacity);
void getCommonArea (Figure **figures, int &size, const int &capacity);

int main () {
    int size = 0, capacity = -1;

    while (capacity <= 0) {
        std::cout << "Input array capacity: ";
        std::cin >> capacity;
    }
    
    Figure **figures = new Figure*[capacity];
    for (int i = 0; i < size; i++) figures[i] = nullptr;

    bool work = true;

    while (work) {
        std::cout << std::endl << "================" << std::endl;
        std::cout << "Input action index:" << std::endl;
        std::cout << "0 - exit" << std::endl;
        std::cout << "1 - input figure" << std::endl;
        std::cout << "2 - delete figure" << std::endl;
        std::cout << "3 - print info" << std::endl;
        std::cout << "4 - get common area" << std::endl;

        int action;
        std::cin >> action;

        switch (action) {
        case 0:
            std::cout << std::endl << "Work is done" << std::endl; 
            work = false;
            break;

        case 1:
            addFigure(figures, size, capacity);
            break;

        case 2:
            deleteFigure(figures, size, capacity);
            break;
        
        case 3:
            printInfo(figures, size, capacity);
            break;
        
        case 4:
            getCommonArea(figures, size, capacity);
            break;
    
        default:
            std::cout << "Unknown action: " << action << std::endl;
        }   
    }

    for (int i = 0; i < size; i++) delete figures[i];
    delete[] figures;

    return 0;
}

void addFigure (Figure **figures, int &size, const int &capacity) {
    std::cout << std::endl;

    if (size >= capacity) {
        std::cout << "Unable to add figure, array is full" << std::endl;
        return;
    }

    Figure *figureToAdd = nullptr;

    bool work = true;

    while (work) {
        std::cout << std::endl << "Input figure type to add: " << std::endl;
        std::cout << "0 - cancel" << std::endl;
        std::cout << "1 - Triangle" << std::endl;
        std::cout << "2 - Hexagon" << std::endl;
        std::cout << "3 - Octagon" << std::endl;

        int figureType;
        std::cin >> figureType;

        bool skip = false;

        switch (figureType) {
        case 0:
            return;
        
        case 1:
            figureToAdd = new Triangle;
            break;
        
        case 2:
            figureToAdd = new Hexagon;
            break;

        case 3:
            figureToAdd = new Octagon;
            break;

        default:
            std::cout << "Unknown figure type: " << figureType << std::endl;
            skip = true;
        }

        if (skip) continue;
        
        std::cout << std::endl;

        try {
            std::cin >> *figureToAdd;
            work = false;
        } catch (const std::exception &error) {
            delete figureToAdd;
            std::cout << error.what() << std::endl;
        }
    }
    
    delete figures[size];
    figures[size] = figureToAdd;
    size++;

    std::cout << "Figure successfully added" << std::endl;
}

void deleteFigure (Figure **figures, int &size, const int &capacity) {
    std::cout << std::endl;

    if (size <= 0) {
        std::cout << "Unable to delete figure, array is empty" << std::endl;
        return;
    }

    int index = -1;
    while (index < 0 || index >= size) {
        std::cout << "Input index between 0 and " << size << ": ";
        std::cin >> index;
    }

    if (figures[index] == nullptr) {
        std::cout << "No figure by index " << index << std::endl;
        return;
    }

    delete figures[index];
    
    size--;

    for (int i = index; i < size; i++) {
        figures[i] = figures[i + 1];
    }

    figures[size] = nullptr;

    std::cout << "Figure successfully deleted, other figures were shifted on its place" << std::endl;
}

void printInfo (Figure **figures, int &size, const int &capacity) {
    std::cout << std::endl << "Figures (size: " << size << ", capacity: " << capacity << "):" << std::endl << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << "Figure on index " << i << ": " << std::endl;
        std::cout << *figures[i] << std::endl;
        std::cout << "Rotation center: " << figures[i]->calcRotationCenter() << std::endl;
        std::cout << "Area: " << static_cast<double>(*figures[i]) << std::endl << std::endl;
    }
}

void getCommonArea (Figure **figures, int &size, const int &capacity) {
    double commonArea = 0.0;

    for (int i = 0; i < size; i++) {
        if (figures[i] == nullptr) continue;

        commonArea += static_cast<double>(*figures[i]);
    }

    std::cout << std::endl << "Common area is " << commonArea << std::endl;
}
