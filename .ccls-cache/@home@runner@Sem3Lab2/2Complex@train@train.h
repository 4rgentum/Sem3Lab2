#ifndef TRAIN_H
#define TRAIN_H

#include "train/wagon.h"

using namespace lab2SimpleClass;

namespace lab2ComplexClass {

  const int MAX_WAGONS = 10; // Максимальное количество вагонов в поезде

  class Train {
    private:
      Wagon wagons[MAX_WAGONS]; // Массив вагонов
      int numWagons; // Текущее количество вагонов в поезде

    public:
      Train(); // Конструктор по умолчанию

      explicit Train(const Wagon wagons[], int numWagons); // Конструктор с инициализацией вагонов из массива

      explicit Train(const Wagon &wagon); // Конструктор с инициализацией одним вагоном

      void readFromInput(); // Метод для ввода состояния поезда

      void writeToOutput() const; // Метод для вывода состояния поезда

      void addWagon(const Wagon &wagon); // Метод добавления вагона в поезд

      const Wagon& getWagonByIndex(int index) const; // Метод получения вагона по его номеру (возврат по ссылке)

      void removeWagonByIndex(int index); //Удаление вагона с заданным номером из поезда
  
      // Усадить заданное число пассажиров в наиболее свободный вагон заданного класса
      void boardPassengersToMostAvailableWagon(int passengers, WagonType wagonType); 

      // Вспомогательный метод который возвращает сколько чиловек в поезде в данном типе вагонов и сколько всего в этиъ вагонах может быть человек
      void getPassengerCountByType(lab2SimpleClass::WagonType wagonType, int& occupiedSeats, int& maxCapacity);
    
      // перераспределить пассажиров между вагонами таким образом, чтобы процент занятости всех вагонов был максимально близок
      void redistributePassengers();

      // Минимизировать количество вагонов, освободив лишние путём пересадки пассажиров между вагонами и удалив их из вектора
      void optimizeTrain();

      // Вспомагетльный метод добавления по индексу
    void addWagonAtIndex(const Wagon& newWagon, int index);
  
      // Поместить вагон-ресторан оптимальным образом, то есть таким, чтобы до и после него в поезде было примерно одинаковое количество пассажиров
      void optimizeRestaurantPlacement();
  };
  
} // namespace lab2ComplexClass

#endif // TRAIN_H