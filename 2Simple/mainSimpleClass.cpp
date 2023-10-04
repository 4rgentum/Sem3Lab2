#include <iostream>
#include "wagon/wagon.h"

int main() {
    std::cout << "Welcome to the Wagon Management System!" << std::endl;

    try {
        lab2SimpleClass::Wagon wagon1;
        wagon1.readFromInput();

        lab2SimpleClass::Wagon wagon2(lab2SimpleClass::WagonType::ECONOMY);
        wagon2.readFromInput();

        std::cout << "Wagon 1 Information:" << std::endl;
        wagon1.writeToOutput();

        std::cout << "Wagon 2 Information:" << std::endl;
        wagon2.writeToOutput();

        wagon1.transferPassengers(wagon2);
        
        std::cout << "After Passenger Transfer:" << std::endl;
        std::cout << "Wagon 1 Information:" << std::endl;
        wagon1.writeToOutput();

        std::cout << "Wagon 2 Information:" << std::endl;
        wagon2.writeToOutput();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}