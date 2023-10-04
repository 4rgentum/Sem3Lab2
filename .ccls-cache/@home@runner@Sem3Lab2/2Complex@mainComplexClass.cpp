#include "train/train.h"
#include <iostream>

using namespace lab2SimpleClass;
using namespace lab2ComplexClass;

int main() {
  try {
    // Создаем несколько вагонов
    Wagon wagon1(WagonType::SITTING);
    Wagon wagon2(WagonType::ECONOMY);
    Wagon wagon3(WagonType::LUXURY);
    
    // Создаем поезд и добавляем вагоны
    Train train;
    train.addWagon(wagon1);
    train.addWagon(wagon2);
    train.addWagon(wagon3);

    std::cout << "Initial Train State:" << std::endl;
    train.writeToOutput();

    // Вводим вагон из входного потока
    Wagon wagonFromInput;
    std::cout << "Enter details for a new wagon:" << std::endl;
    wagonFromInput.readFromInput();

    // Добавляем вагон в поезд
    train.addWagon(wagonFromInput);

    std::cout << "\nTrain State After Adding Wagon from Input:" << std::endl;
    train.writeToOutput();

    // Добавляем пассажиров в наиболее свободные вагоны
    train.boardPassengersToMostAvailableWagon(50, WagonType::SITTING);
    train.boardPassengersToMostAvailableWagon(30, WagonType::ECONOMY);
    train.boardPassengersToMostAvailableWagon(20, WagonType::LUXURY);

    std::cout << "\nTrain State After Boarding Passengers:" << std::endl;
    train.writeToOutput();

    // Перераспределяем пассажиров
    train.redistributePassengers();

    std::cout << "\nTrain State After Redistributing Passengers:" << std::endl;
    train.writeToOutput();

    // Оптимизируем поезд
    train.optimizeTrain();

    std::cout << "\nTrain State After Optimizing Train:" << std::endl;
    train.writeToOutput();

    // Помещаем ресторан-вагон оптимальным образом
    train.optimizeRestaurantPlacement();

    std::cout << "\nTrain State After Optimizing Restaurant Placement:" << std::endl;
    train.writeToOutput();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}