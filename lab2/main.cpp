#include <iostream>
#include "src/binary.cpp"

int main()
{
    try
    {
        std::string bin1, bin2;
        std::cout << "Enter first binary number: ";
        std::cin >> bin1;

        std::cout << "Enter second binary number: ";
        std::cin >> bin2;

        Binary Numb1(bin1);
        Binary Numb2(bin2);

        Numb1 += Numb2;

        std::cout << "Result of addition: ";
        for (size_t i = 0; i < Numb1.getSize(); ++i)
        {
            std::cout << Numb1.getData()[i];
        }
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
