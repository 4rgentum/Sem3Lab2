#include "wagon.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace lab2SimpleClass {
  // Неявный конструктор (конструктор по умолчанию)
  Wagon::Wagon() : maxCapacity(0), occupiedSeats(0), type(WagonType::RESTAURANT) {}

  // Явный конструктор с параметрами
  Wagon::Wagon(int maxCapacity, int occupiedSeats, WagonType type) : maxCapacity(maxCapacity), occupiedSeats(occupiedSeats), type(type) {
    if (type == WagonType::RESTAURANT) {
      throw std::invalid_argument("Restaurant wagons cannot have capacity or occupied seats.");
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
          throw std::invalid_argument("Wagon is full. Cannot board more passengers.");
        }
      }
    } catch (const std::exception &e) {
      //std::cerr << "Error: " << e.what() << std::endl;
      throw;
    }
  }

  // Метод для высадки заданного числа пассажиров из вагона
  void Wagon::disembarkPassengers(int passengers) {
    try {
      if (maxCapacity != 0) {
        occupiedSeats -= passengers;
        if (occupiedSeats < 0) {
          occupiedSeats += passengers;
          throw std::invalid_argument("There are not enough people in the Wagon to disembark.");
        }
      }
    } catch (const std::exception &e) {
      //std::cerr << "Error: " << e.what() << std::endl;
      throw;
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
      throw;
    }  
  }

  void Wagon::setType(WagonType wagonType) { type = wagonType; }

  // Метод для ввода состояния вагона
  void Wagon::readFromInput() {
    try {
      std::cin >> maxCapacity;
      std::cin >> occupiedSeats;

      int typeInt;
      std::cin >> typeInt;
      type = static_cast<WagonType>(typeInt);

      if (type == WagonType::RESTAURANT) {
        maxCapacity = 0;
      }

      if (maxCapacity < 0 || occupiedSeats < 0 || (maxCapacity < occupiedSeats && maxCapacity != 0) || typeInt < 0 || typeInt > 3) {
        throw;
      }
    } catch (const std::exception& e) {
      //std::cerr << "Error while reading wagon from input: " << e.what() << std::endl;
      throw std::invalid_argument("Error while reading wagon from input.");
    }
  }

  // Метод для вывода состояния вагона
  void Wagon::writeToOutput() const {
    try {
      std::cout << getMaxCapacity() << " " << getOccupiedSeats() << " " << static_cast<int>(getType()) << std::endl;
    } catch (const std::exception& e) {
        //std::cerr << "Error while writing wagon to output: " << e.what() << std::endl;
        throw std::invalid_argument("Error while reading wagon from output.");
    }
  }

  // Метод для пересадки пассажиров из текущего вагона в другой
  void Wagon::transferPassengers(Wagon &otherWagon) {
    if (type == WagonType::RESTAURANT || otherWagon.getType() == WagonType::RESTAURANT) {
      throw std::invalid_argument("Passengers cannot be transferred to or from a restaurant wagon.");
    }

    try {
      if (getType() != otherWagon.getType()) {
         throw;
      } else {
        int totalOccupiedSeats = occupiedSeats + otherWagon.getOccupiedSeats();
        int totalMaxCapacity = maxCapacity + otherWagon.getMaxCapacity();
    
        // Вычисляем процентное соотношение занятых мест в среднем
        double occupancyPercentageMid = static_cast<double>(totalOccupiedSeats) / totalMaxCapacity;
    
        // Вычисляем количество пассажиров для пересадки на основе процентного соотношения
        int passengersThis = static_cast<int>(occupancyPercentageMid * maxCapacity);
        int passengersOther = static_cast<int>(occupancyPercentageMid * otherWagon.maxCapacity);
    
        // Обновляем количество занятых мест в обоих вагонах
        setOccupiedSeats(passengersThis);
        otherWagon.setOccupiedSeats(passengersOther);
      }
    } catch (const std::exception &e) {
      // Обработка исключений, если что-то идет не так во время пересадки
      //std::cerr << "Error during passenger transfer: " << e.what() << std::endl;
      throw std::invalid_argument("Error during passenger transfer.");
    }
  }

  // Перегрузка оператора >> при перемещении пассажиров из одного вагона в другой
  Wagon &Wagon::operator >>(Wagon &other) {
    this->transferPassengers(other);
    return *this;
  }

  // Перегрузка оператора >> для ввода экземляра вагона
  std::istream& operator>>(std::istream& is, Wagon& wagon) {
    wagon.readFromInput();
    return is;
  }
  
  // Реализация перегрузки оператора "<<" для вывода вагона в выходной поток
  std::ostream& operator<<(std::ostream& os, const Wagon& wagon) {
    wagon.writeToOutput();
    return os;
  }

} // namespace lab2SimpleClass