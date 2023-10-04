#include "Train.h"
#include <iostream>

using namespace lab2SimpleClass;

namespace lab2ComplexClass {

  // Конструктор по умолчанию
  Train::Train() : numWagons(0) {} // Инициализируем пустой поезд

  // Конструктор с инициализацией вагонов из массива
  Train::Train(const Wagon wagons[], int numWagons) : numWagons(numWagons) {
    // Инициализируем поезд вагонами из переданного массива
    if (numWagons > MAX_WAGONS) {
      throw std::invalid_argument("Number of wagons exceeds the maximum allowed.");
    }

    for (int i = 0; i < numWagons; ++i) {
      this->wagons[i] = wagons[i];
    }
  }

  // Конструктор с инициализацией одним вагоном
  Train::Train(const Wagon &wagon) : numWagons(1) {
    // Инициализируем поезд одним вагоном
    wagons[0] = wagon;
  }

  // Метод для ввода состояния поезда
  void Train::readFromInput() {
    try {
      // Считываем количество вагонов
      std::cin >> numWagons;

      if (numWagons > MAX_WAGONS) {
        throw std::invalid_argument("Number of wagons exceeds the maximum allowed.");
      }

      // Считываем информацию о каждом вагоне
      for (int i = 0; i < numWagons; ++i) {
        wagons[i].readFromInput();
      }
    } catch (const std::exception& e) {
      std::cerr << "Error while reading train from input: " << e.what() << std::endl;
      throw;
    }
  }

  // Метод для вывода состояния поезда
  void Train::writeToOutput() const {
    try {
      // Выводим количество вагонов
      std::cout << numWagons << std::endl;

      // Выводим информацию о каждом вагоне
      for (int i = 0; i < numWagons; ++i) {
        wagons[i].writeToOutput();
      }
    } catch (const std::exception& e) {
      std::cerr << "Error while writing train to output: " << e.what() << std::endl;
      throw;
    }
  }

  // Метод добавления вагона в поезд
  void Train::addWagon(const Wagon &wagon) {
  try {
    if (numWagons >= MAX_WAGONS) {
      throw std::overflow_error("Maximum number of wagons reached.");
    }

    wagons[numWagons++] = wagon;
  } catch (const std::exception &e) {
    std::cerr << "Error while adding wagon to train: " << e.what() << std::endl;
    throw;
  }
}

  // Метод получения вагона по его номеру (возврат по ссылке)
  const Wagon& Train::getWagonByIndex(int index) const {
    try {
      if (index < 0 || index >= numWagons) {
        throw std::out_of_range("Invalid wagon index.");
      }

      return wagons[index];
    } catch (const std::exception &e) {
      std::cerr << "Error while getting wagon by index: " << e.what() << std::endl;
      throw;
    }
  }

  //удаление вагона с заданным номером из поезда
  void Train::removeWagonByIndex(int index) {
    try {
      if (index < 0 || index >= numWagons) {
        throw std::out_of_range("Invalid wagon index.");
      }

      // Сдвигаем все вагоны после удаляемого влево
      for (int i = index; i < numWagons - 1; ++i) {
        wagons[i] = wagons[i + 1];
      }

      // Уменьшаем количество вагонов в поезде
      --numWagons;
    } catch (const std::exception &e) {
      std::cerr << "Error while removing wagon by index: " << e.what() << std::endl;
      throw;
    }
  }

  // Усадить заданное число пассажиров в наиболее свободный вагон заданного класса
  void Train::boardPassengersToMostAvailableWagon(int passengers, WagonType wagonType) {
    try {
  
      int availableWagonsCount = 0;
      int availableWagonsIndices[MAX_WAGONS];
      double availableWagonsOccupancy[MAX_WAGONS];
  
      // Найдем все вагоны заданного типа, которые могут вместить заданное число пассажиров
      for (int i = 0; i < numWagons; ++i) {
        if (wagons[i].getType() == wagonType && wagons[i].getMaxCapacity() - wagons[i].getOccupiedSeats() >= passengers) {
          availableWagonsIndices[availableWagonsCount] = i;
          availableWagonsOccupancy[availableWagonsCount] = wagons[i].getOccupancyPercentage();
          ++availableWagonsCount;
        }
      }
  
      if (availableWagonsCount == 0) {
        throw std::runtime_error("No available wagons of the specified type can accommodate the specified number of passengers.");
      }
  
      int mostAvailableIndex = availableWagonsIndices[0];
      double mostAvailablePercentage = availableWagonsOccupancy[0];
  
      // Найдем наиболее свободный вагон среди доступных
      for (int i = 1; i < availableWagonsCount; ++i) {
        if (availableWagonsOccupancy[i] > mostAvailablePercentage) {
          mostAvailableIndex = availableWagonsIndices[i];
          mostAvailablePercentage = availableWagonsOccupancy[i];
        }
      }
  
      // Посадка пассажиров в наиболее свободный вагон заданного класса
      wagons[mostAvailableIndex].boardPassengers(passengers);
    } catch (const std::exception &e) {
      std::cerr << "Error while boarding passengers: " << e.what() << std::endl;
      throw;
    }
  }

  // Вспомогательный метод который возвращает сколько чиловек в поезде в данном типе вагонов и сколько всего в этиъ вагонах может быть человек
  void Train::getPassengerCountByType(lab2SimpleClass::WagonType wagonType, int& occupiedSeats, int& maxCapacity) {
    occupiedSeats = 0;
    maxCapacity = 0;

    for (int i = 0; i < numWagons; i++) {
        if (wagons[i].getType() == wagonType) {
            occupiedSeats += wagons[i].getOccupiedSeats();
            maxCapacity += wagons[i].getMaxCapacity();
        }
    }
}
  
  // Перераспределить пассажиров между вагонами таким образом, чтобы процент занятости всех вагонов был максимально близок
  void Train::redistributePassengers() {
    
    int occupiedSeatsByEconomy,  occupiedSeatsBySitting, occupiedSeatsByLuxury, maxCapacityByEconomy, maxCapacityBySitting, maxCapacityByLuxury;
    
    // Определяем сколько занято и сколько всего мест для каждого типа вагонов
    getPassengerCountByType(lab2SimpleClass::WagonType::SITTING, occupiedSeatsBySitting, maxCapacityBySitting);
    getPassengerCountByType(lab2SimpleClass::WagonType::ECONOMY, occupiedSeatsByEconomy, maxCapacityByEconomy);
    getPassengerCountByType(lab2SimpleClass::WagonType::LUXURY, occupiedSeatsByLuxury, maxCapacityByLuxury);

    // Считаем среднюю процентную занятость для каждого типа вагонов
    double occupancyPercentageMidSitting = static_cast<double>(occupiedSeatsBySitting) / maxCapacityBySitting;
    double occupancyPercentageMidEconomy = static_cast<double>(occupiedSeatsByEconomy) / maxCapacityByEconomy;
    double occupancyPercentageMidLuxury = static_cast<double>(occupiedSeatsByLuxury) / maxCapacityByLuxury;

    // Заполняем средним значением
    for (int i = 0; i < numWagons; i++) {
      if (wagons[i].getType() == lab2SimpleClass::WagonType::SITTING) {
        wagons[i].setOccupiedSeats(static_cast<int>(wagons[i].getMaxCapacity() * occupancyPercentageMidSitting));
      } else if (wagons[i].getType() == lab2SimpleClass::WagonType::ECONOMY) {
        wagons[i].setOccupiedSeats(static_cast<int>(wagons[i].getMaxCapacity() * occupancyPercentageMidEconomy));
      } else if (wagons[i].getType() == lab2SimpleClass::WagonType::LUXURY) {
        wagons[i].setOccupiedSeats(static_cast<int>(wagons[i].getMaxCapacity() * occupancyPercentageMidLuxury));
      }
    }
    
  }

  // Минимизировать количество вагонов, освободив лишние путём пересадки пассажиров между вагонами и удалив их из вектора
  void Train::optimizeTrain() {
    int occupiedSeatsByEconomy,  occupiedSeatsBySitting, occupiedSeatsByLuxury, maxCapacityByEconomy, maxCapacityBySitting, maxCapacityByLuxury;
    
    // Определяем сколько занято и сколько всего мест для каждого типа вагонов
    getPassengerCountByType(lab2SimpleClass::WagonType::SITTING, occupiedSeatsBySitting, maxCapacityBySitting);
    getPassengerCountByType(lab2SimpleClass::WagonType::ECONOMY, occupiedSeatsByEconomy, maxCapacityByEconomy);
    getPassengerCountByType(lab2SimpleClass::WagonType::LUXURY, occupiedSeatsByLuxury, maxCapacityByLuxury);

    for (int i = 0; i < numWagons; i++) {
      
      if (wagons[i].getType() == lab2SimpleClass::WagonType::SITTING) {
        if (occupiedSeatsBySitting > 0) {
          wagons[i].setOccupiedSeats(wagons[i].getMaxCapacity());
          occupiedSeatsBySitting -= wagons[i].getMaxCapacity();
        } else {
          wagons[i].setOccupiedSeats(0);
        }
      }

      if (wagons[i].getType() == lab2SimpleClass::WagonType::ECONOMY) {
        if (occupiedSeatsByEconomy > 0) {
          wagons[i].setOccupiedSeats(wagons[i].getMaxCapacity());
          occupiedSeatsByEconomy -= wagons[i].getMaxCapacity();
        } else {
          wagons[i].setOccupiedSeats(0);
        }
      }

      if (wagons[i].getType() == lab2SimpleClass::WagonType::LUXURY) {
        if (occupiedSeatsByLuxury > 0) {
          wagons[i].setOccupiedSeats(wagons[i].getMaxCapacity());
          occupiedSeatsByLuxury -= wagons[i].getMaxCapacity();
        } else {
          wagons[i].setOccupiedSeats(0);
        }
      }
      
    }

    for (int j = 0; j < numWagons; j++) {
      if (wagons[j].getOccupiedSeats() == 0) {
        removeWagonByIndex(j);
        j--;
      }
    }
    
  }

  // Вспомагетльный метод добавления по индексу
  void Train::addWagonAtIndex(const Wagon& newWagon, int index) {
    try {
        if (index < 0 || index > numWagons) {
            throw std::invalid_argument("Invalid index for adding a wagon.");
        }

        // Сначала сдвигаем вагоны на одну позицию вперед, начиная с последнего
        for (int i = numWagons; i > index; i--) {
            wagons[i] = wagons[i - 1];
        }

        // Вставляем новый вагон на указанный индекс
        wagons[index] = newWagon;

        // Увеличиваем количество вагонов
        numWagons++;
    } catch (const std::exception& e) {
        std::cerr << "Error when adding a wagon: " << e.what() << std::endl;
    }
  }
  
  // Поместить вагон-ресторан оптимальным образом, то есть таким, чтобы до и после него в поезде было примерно одинаковое количество пассажиров
  void Train::optimizeRestaurantPlacement() {
    int totalPassengers = 0;
    for (int i = 0; i < numWagons; i++) {
      totalPassengers += wagons[i].getOccupiedSeats();
    }

    int midPassengers = totalPassengers / 2;
    int needPosition = 0;
    for (int j = 0; j < numWagons; j++) {
      totalPassengers -= wagons[j].getOccupiedSeats();
      if (totalPassengers > midPassengers) {
        j--;
        needPosition = j;
        break;
      } else if (totalPassengers == midPassengers) {
        needPosition = j;
      }
    }
    
    // Вставляем ресторан-вагон на оптимальную позицию
    Wagon restaurantWagon;
    restaurantWagon.setType(lab2SimpleClass::WagonType::RESTAURANT);
    addWagonAtIndex(restaurantWagon, needPosition);
    
  }
  
} // namespace lab2ComplexClass