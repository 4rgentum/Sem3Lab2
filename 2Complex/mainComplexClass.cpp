#include "train/train.h"
#include <iostream>

using namespace lab2SimpleClass;
using namespace lab2ComplexClass;

int main() {
  try {
    // Создаем пустой поезд
    Train train1;

    // Создаем вагоны для поезда
    Wagon wagon1(50, 20, WagonType::ECONOMY);
    Wagon wagon2(100, 40, WagonType::SITTING);
    Wagon wagon3(30, 20, WagonType::LUXURY);

    // Добавляем вагоны в поезд
    train1 += wagon1;
    train1 += wagon2;
    train1 += wagon3;

    // Выводим информацию о поезде
    std::cout << "Train 1:" << std::endl;
    std::cout << train1;

    // Добавляем пассажиров в наиболее свободный вагон
    train1.boardPassengersToMostAvailableWagon(10, WagonType::ECONOMY);

    // Выводим информацию о поезде после посадки пассажиров
    std::cout << "Train 1 after boarding passengers:" << std::endl;
    std::cout << train1;

    // Перераспределяем пассажиров
    train1.redistributePassengers();

    // Выводим информацию о поезде после перераспределения пассажиров
    std::cout << "Train 1 after redistributing passengers:" << std::endl;
    std::cout << train1;

    // Минимизируем количество вагонов
    train1.optimizeTrain();

    // Выводим информацию о поезде после оптимизации
    std::cout << "Train 1 after optimization:" << std::endl;
    std::cout << train1;

    // Создаем еще один поезд с помощью конструктора с инициализацией из массива вагонов
    Wagon wagons[] = {wagon1, wagon2, wagon3};
    Train train2(wagons, 3);

    // Выводим информацию о втором поезде
    std::cout << "Train 2:" << std::endl;
    std::cout << train2;

    return 0;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}