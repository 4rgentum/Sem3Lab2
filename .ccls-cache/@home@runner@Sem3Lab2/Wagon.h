#ifndef WAGON_H
#define WAGON_H

#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace lab2SimpleClass {

  // шаблонная функция ввода одного числа
  template <class T>
  T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
    T a;
    while (true) {
      std::cin >> a;
      if (std::cin.eof()) { // обнаружен конец файла
        throw std::runtime_error("Failed to read number: EOF");
      } else if (std::cin.bad()) { // обнаружена невосстановимая ошибка входного
                                 // потока
        throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
      } else if (std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
        std::cin.clear(); // очищаем флаги состояния потока
        // игнорируем все символы до конца строки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "You are wrong; repeat please!" << std::endl;
      } else if (a >= min && a <= max) { // если число входит в заданный диапазон
        return a;
      } else {
        std::cerr << "Number out of range. Please enter a valid number." << std::endl;
      }
    }
  }

  // Определение перечисления для типов вагонов
  enum class WagonType { SITTING, ECONOMY, LUXURY, RESTAURANT };

  class Wagon {
    private:
      int maxCapacity;
      int occupiedSeats;
      WagonType type;

    public:
      Wagon(); // Неявный конструктор (конструктор по умолчанию)
      Wagon(int maxCapacity, int occupiedSeats, WagonType type); // Явный конструктор с параметрами
      Wagon(WagonType type); // Явный конструктор с инициализацией только типом
      
      double getOccupancyPercentage() const; // Метод для получения процента занятости вагона

      void boardPassengers(int passengers); // Метод для посадки заданного числа пассажиров в вагон
      void disembarkPassengers(int passengers); // Метод для высадки заданного числа пассажиров из вагона

      // Геттеры для получения значений атрибутов класса
      int getMaxCapacity() const;
      int getOccupiedSeats() const;
      WagonType getType() const;

      // Сеттеры для изменения значений атрибутов класса
      void setMaxCapacity(int capacity);
      void setOccupiedSeats(int seats);
      void setType(WagonType wagonType);

      void readFromInput(); // Метод для ввода состояния вагона
      void writeToOutput() const; // Метод для вывода состояния вагона
      
      void transferPassengers(Wagon &otherWagon); // Метод для пересадки пассажиров из текущего вагона в другой
  };
  
} // namespace lab2SimpleClass

#endif // WAGON_H