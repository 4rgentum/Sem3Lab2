#include <iostream>
#include "wagon/wagon.h"

int main() {
  try {
    using namespace lab2SimpleClass;
    
    // Создаем неявный вагон (ресторан)
    Wagon restaurantWagon;
    
    // Создаем явный вагон с параметрами
    Wagon sittingWagon(100, 30, WagonType::SITTING);
  
    // Создаем явный вагон с инициализацией только типом
    Wagon luxuryWagon(WagonType::LUXURY);
  
    // Выводим информацию о вагонах
    std::cout << "Restaurant Wagon:" << std::endl << restaurantWagon << std::endl;
    std::cout << "Sitting Wagon:" << std::endl << sittingWagon << std::endl;
    std::cout << "Luxury Wagon:" << std::endl << luxuryWagon << std::endl;
  
    // Пересаживаем пассажиров из sittingWagon в luxuryWagon
    //sittingWagon.transferPassengers(luxuryWagon);
  
    // Выводим информацию о вагонах после пересадки
    std::cout << "Sitting Wagon (after transfer):" << std::endl << sittingWagon << std::endl;
    std::cout << "Luxury Wagon (after transfer):" << std::endl << luxuryWagon << std::endl;
  
    // Перемещаем пассажиров из sittingWagon в luxuryWagon с использованием оператора >>
    //sittingWagon >> luxuryWagon;
  
    // Выводим информацию о вагонах после перемещения с использованием оператора >>
    std::cout << "Sitting Wagon (after move):" << std::endl << sittingWagon << std::endl;
    std::cout << "Luxury Wagon (after move):" << std::endl << luxuryWagon << std::endl;
  
    // Вводим данные о вагоне с помощью оператора >>
    Wagon inputWagon;
    std::cout << "Enter data for a new wagon (maxCapacity occupiedSeats type): ";
    std::cin >> inputWagon;
  
    // Выводим информацию о вновь созданном вагоне
    std::cout << "Input Wagon:" << std::endl << inputWagon << std::endl;
  
    inputWagon >> sittingWagon;
    
    std::cout << "Sitting Wagon:" << std::endl << sittingWagon << std::endl;
    std::cout << "Input Wagon:" << std::endl << inputWagon << std::endl;
  } catch (const std::exception& e) {
    // В случае ошибки выводим сообщение об ошибке
    std::cerr << "Error: " << e.what() << std::endl;
  }
  
  return 0;
}