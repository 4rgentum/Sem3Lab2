#include "Lab2PrimaryClass.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace lab2PrimaryClass {
// Неявный конструктор (конструктор по умолчанию)
Wagon::Wagon()
    : maxCapacity(0), occupiedSeats(0), type(WagonType::RESTAURANT) {}

// Явный конструктор с параметрами
Wagon::Wagon(int maxCapacity, int occupiedSeats, WagonType type)
    : maxCapacity(maxCapacity), occupiedSeats(occupiedSeats), type(type) {
  if (type == WagonType::RESTAURANT) {
    throw std::invalid_argument(
        "Restaurant wagons cannot have capacity or occupied seats.");
  }
}

// Явный конструктор с инициализацией только типом
Wagon::Wagon(WagonType type) : type(type) {
  // Устанавливаем вместимость в зависимости от типа
  switch (type) {
  case WagonType::SITTING:
    maxCapacity = 100; // Пример значения для сидячего вагона
    occupiedSeats = 0; // И количество занятых мест
    break;
  case WagonType::ECONOMY:
    maxCapacity = 50; // Пример значения для вагона эконом-класса
    occupiedSeats = 0; // И количество занятых мест
    break;
  case WagonType::LUXURY:
    maxCapacity = 30; // Пример значения для вагона люкс
    occupiedSeats = 0; // И количество занятых мест
    break;
  case WagonType::RESTAURANT:
    maxCapacity = 0; // Вместимость для ресторана всегда 0
    occupiedSeats = 0; // И количество занятых мест
    break;
  }
}

// Метод для получения процента занятости вагона
double Wagon::getOccupancyPercentage() const {
  if (maxCapacity == 0) {
    return 0.0; // Если вагон ресторан, занятость всегда 0%
  }
  return static_cast<double>(occupiedSeats) / maxCapacity * 100.0;
}

// Метод для посадки заданного числа пассажиров в вагон
void Wagon::boardPassengers(int passengers) {
  try {
    if (maxCapacity != 0) {
      occupiedSeats += passengers;
      if (occupiedSeats > maxCapacity) {
        occupiedSeats -= passengers;
        throw std::invalid_argument(
            "Wagon is full. Cannot board more passengers.");
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

// Метод для высадки заданного числа пассажиров из вагона
void Wagon::disembarkPassengers(int passengers) {
  try {
    if (maxCapacity != 0) {
      occupiedSeats -= passengers;
      if (occupiedSeats < 0) {
        occupiedSeats += passengers;
        throw std::invalid_argument(
            "There are not enough people in the Wagon to disembark.");
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

// Геттеры для получения значений атрибутов класса
int Wagon::getMaxCapacity() const { return maxCapacity; }

int Wagon::getOccupiedSeats() const { return occupiedSeats; }

WagonType Wagon::getType() const { return type; }

// Сеттеры для изменения значений атрибутов класса
void Wagon::setMaxCapacity(int capacity) { maxCapacity = capacity; }

void Wagon::setOccupiedSeats(int seats) {
  try {
    if (seats < 0 || seats > maxCapacity) {
      throw std::invalid_argument("Invalid number of occupied seats.");
    }
    occupiedSeats = seats;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void Wagon::setType(WagonType wagonType) { type = wagonType; }

// Методы для ввода и вывода состояния класса в потоки
void Wagon::printInfo() const {
  std::cout << "Type: ";
  switch (type) {
  case WagonType::SITTING:
    std::cout << "Sitting";
    break;
  case WagonType::ECONOMY:
    std::cout << "Economy";
    break;
  case WagonType::LUXURY:
    std::cout << "Luxury";
    break;
  case WagonType::RESTAURANT:
    std::cout << "Restaurant";
    break;
  }
  std::cout << ", Max Capacity: " << maxCapacity
            << ", Occupied Seats: " << occupiedSeats
            << ", Occupancy Percentage: " << getOccupancyPercentage() << "%"
            << std::endl;
}

// Метод для пересадки пассажиров из текущего вагона в другой
void Wagon::transferPassengers(Wagon &otherWagon) {
  if (type == WagonType::RESTAURANT ||
      otherWagon.getType() == WagonType::RESTAURANT) {
    throw std::invalid_argument(
        "Passengers cannot be transferred to or from a restaurant wagon.");
  }

  double bestDifference = calculateOccupancyDifference(otherWagon);
  Wagon bestThis(*this);
  Wagon bestOther(otherWagon);

  try {

    // Дополнительная проверка для случая, когда процентная занятость вагона
    // назначения больше, чем вагона отправления
    if (static_cast<double>(otherWagon.getOccupiedSeats()) /
            otherWagon.getMaxCapacity() >
        static_cast<double>(occupiedSeats) / maxCapacity) {
      throw std::invalid_argument(
          "Passenger transfer is not possible due to occupancy conditions.");
    }

    for (int i = occupiedSeats; i > 0; --i) {
      boardPassengers(-1); // Убираем одного пассажира из текущего вагона
      otherWagon.boardPassengers(1); // Пересаживаем его в другой вагон

      double newDifference = calculateOccupancyDifference(otherWagon);
      if (newDifference <= bestDifference) {
        bestDifference = newDifference;
        bestThis = *this;
        bestOther = otherWagon;
      } else {
        // Возвращаемся на предыдущее состояние
        *this = bestThis;
        otherWagon = bestOther;
        break;
      }
    }
  } catch (const std::exception &e) {
    // Обработка исключений, если что-то идет не так во время пересадки
    std::cerr << "Error during passenger transfer: " << e.what() << std::endl;
    *this = bestThis;
    otherWagon = bestOther;
  }
}

} // namespace lab2PrimaryClass