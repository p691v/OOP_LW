#include <iostream>
#include "include/divider.h"

int main() {
    int a, b;
    std::cout << "Enter length and width of your chocolate bar:" << std::endl;
    std::cin >> a >> b;
    int result = divider(a, b);
    if (result == -1){
        std::cout << "Incorrect input!" << std::endl;
        return 0;
    }
    if (result == 1)
        std::cout << "You have to make " << result << " division" << std::endl;
    else
        std::cout << "You have to make " << result << " divisions" << std::endl;
    return 0;
}
