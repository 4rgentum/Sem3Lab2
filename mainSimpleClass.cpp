#include "Wagon.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept> // Для исключений
#include <string>

/*namespace lab2PrimaryClass {

    // шаблонная функция ввода одного числа
    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max =
std::numeric_limits<T>::max()) { T a; while(true) { std::cin >> a;
            if(std::cin.eof()) { // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            }
            else if(std::cin.bad()) { // обнаружена невосстановимая ошибка
входного потока throw std::runtime_error(std::string("Failed to read number: ")
+ strerror(errno));
            }
            else if(std::cin.fail()) { // прочие ошибки (неправильный формат
ввода) std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
'\n'); std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if(a >= min && a <= max) { // если число входит в заданный
диапазон return a;
            }
            else {
                std::cerr << "Number out of range. Please enter a valid number."
<< std::endl;
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

            // Вспомогательная функция для вычисления разницы в занятости
вагонов double calculateOccupancyDifference(const Wagon& otherWagon) const {
                double occupancyPercentageThis =
static_cast<double>(occupiedSeats) / maxCapacity; double
occupancyPercentageOther = static_cast<double>(otherWagon.getOccupiedSeats()) /
otherWagon.getMaxCapacity(); return std::abs(occupancyPercentageThis -
occupancyPercentageOther);
            }

        public:
            // Неявный конструктор (конструктор по умолчанию)
            Wagon() : maxCapacity(0), occupiedSeats(0),
type(WagonType::RESTAURANT) {}

            // Явный конструктор с параметрами
            Wagon(int maxCapacity, int occupiedSeats, WagonType type) :
maxCapacity(maxCapacity), occupiedSeats(occupiedSeats), type(type) { if (type ==
WagonType::RESTAURANT) { throw std::invalid_argument("Restaurant wagons cannot
have capacity or occupied seats.");
                }
            }

            // Явный конструктор с инициализацией только типом
            Wagon(WagonType type) : type(type) {
                // Устанавливаем вместимость в зависимости от типа
                switch (type) {
                    case WagonType::SITTING:
                        maxCapacity = 100;  // Пример значения для сидячего
вагона occupiedSeats = 0; // И количество занятых мест break; case
WagonType::ECONOMY: maxCapacity = 50; // Пример значения для вагона
эконом-класса occupiedSeats = 0; // И количество занятых мест break; case
WagonType::LUXURY: maxCapacity = 30;  // Пример значения для вагона люкс
                        occupiedSeats = 0; // И количество занятых мест
                        break;
                    case WagonType::RESTAURANT:
                        maxCapacity = 0;   // Вместимость для ресторана всегда 0
                        occupiedSeats = 0; // И количество занятых мест
                        break;
                }
            }

            // Метод для получения процента занятости вагона
            double getOccupancyPercentage() const {
                if (maxCapacity == 0) {
                    return 0.0; // Если вагон ресторан, занятость всегда 0%
                }
                return static_cast<double>(occupiedSeats) / maxCapacity * 100.0;
            }

            // Метод для посадки заданного числа пассажиров в вагон
            void boardPassengers(int passengers) {
                try {
                    if (maxCapacity != 0) {
                        occupiedSeats += passengers;
                        if (occupiedSeats > maxCapacity) {
                            occupiedSeats -= passengers;
                            throw std::invalid_argument("Wagon is full. Cannot
board more passengers.");
                        }
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }

            // Метод для высадки заданного числа пассажиров из вагона
            void disembarkPassengers(int passengers) {
                try {
                    if (maxCapacity != 0) {
                        occupiedSeats -= passengers;
                        if (occupiedSeats < 0) {
                            occupiedSeats += passengers;
                            throw std::invalid_argument("There are not enough
people in the Wagon to disembark.");
                        }
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }

            // Геттеры для получения значений атрибутов класса
            int getMaxCapacity() const {
                return maxCapacity;
            }

            int getOccupiedSeats() const {
                return occupiedSeats;
            }

            WagonType getType() const {
                return type;
            }

            // Сеттеры для изменения значений атрибутов класса
            void setMaxCapacity(int capacity) {
                maxCapacity = capacity;
            }

            void setOccupiedSeats(int seats) {
                try {
                    if (seats < 0 || seats > maxCapacity) {
                        throw std::invalid_argument("Invalid number of occupied
seats.");
                    }
                     occupiedSeats = seats;
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }

            void setType(WagonType wagonType) {
                type = wagonType;
            }

            // Методы для ввода и вывода состояния класса в потоки
            void printInfo() const {
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
                          << ", Occupancy Percentage: " <<
getOccupancyPercentage() << "%" << std::endl;
            }

            // Метод для пересадки пассажиров из текущего вагона в другой
            void transferPassengers(Wagon& otherWagon) {
                if (type == WagonType::RESTAURANT || otherWagon.getType() ==
WagonType::RESTAURANT) { throw std::invalid_argument("Passengers cannot be
transferred to or from a restaurant wagon.");
                }

                double bestDifference =
calculateOccupancyDifference(otherWagon); Wagon bestThis(*this); Wagon
bestOther(otherWagon);

                try {

                    // Дополнительная проверка для случая, когда процентная
занятость вагона назначения больше, чем вагона отправления if
(static_cast<double>(otherWagon.getOccupiedSeats()) /
otherWagon.getMaxCapacity() > static_cast<double>(occupiedSeats) / maxCapacity)
{ throw std::invalid_argument("Passenger transfer is not possible due to
occupancy conditions.");
                    }

                    for (int i = occupiedSeats; i > 0; --i) {
                        boardPassengers(-1); // Убираем одного пассажира из
текущего вагона otherWagon.boardPassengers(1); // Пересаживаем его в другой
вагон

                        double newDifference =
calculateOccupancyDifference(otherWagon); if (newDifference <= bestDifference) {
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
                }
                catch (const std::exception& e) {
                    // Обработка исключений, если что-то идет не так во время
пересадки std::cerr << "Error during passenger transfer: " << e.what() <<
std::endl; *this = bestThis; otherWagon = bestOther;
                }
            }
    };
} // namespace lab2PrimaryClass*/

using namespace lab2SimpleClass;

int main() {

  try {
    // Создание объектов с использованием конструкторов
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2(WagonType::ECONOMY);
    Wagon wagon3;

    // Проверка геттеров и сеттеров
    wagon3.setMaxCapacity(75);
    wagon3.setOccupiedSeats(30);
    wagon3.setType(WagonType::LUXURY);

    std::cout << "Wagon 1 type: " << static_cast<int>(wagon1.getType()) << std::endl;
    std::cout << "Wagon 2 max capacity: " << wagon2.getMaxCapacity() << std::endl;
    std::cout << "Wagon 3 occupied seats: " << wagon3.getOccupiedSeats() << std::endl;

    // Вывод информации о вагонах
    std::cout << "Wagon 1 info:" << std::endl;
    wagon1.printInfo();
    std::cout << "Wagon 2 info:" << std::endl;
    wagon2.printInfo();
    std::cout << "Wagon 3 info:" << std::endl;
    wagon3.printInfo();

    // Посадка и высадка пассажиров
    wagon1.boardPassengers(10);
    wagon2.disembarkPassengers(5);

    std::cout << "Wagon 1 info after boarding:" << std::endl;
    wagon1.printInfo();
    std::cout << "Wagon 2 info after disembarking:" << std::endl;
    wagon2.printInfo();

    // Пересадка пассажиров
    wagon1.transferPassengers(wagon2);

    std::cout << "Wagon 1 info after passenger transfer:" << std::endl;
    wagon1.printInfo();
    std::cout << "Wagon 2 info after passenger transfer:" << std::endl;
    wagon2.printInfo();

    // Создание двух вагонов с вводом данных через входной поток
    std::cout << "Enter data for Wagon 4:" << std::endl;
    Wagon wagon4;
    int maxCapacity4 = getNum<int>();
    int occupiedSeats4 = getNum<int>(0, maxCapacity4); // Задаем ограничение на количество занятых мест
    wagon4.setMaxCapacity(maxCapacity4);
    wagon4.setOccupiedSeats(occupiedSeats4);
    wagon4.printInfo();

    std::cout << "Enter data for Wagon 5:" << std::endl;
    Wagon wagon5;
    int maxCapacity5 = getNum<int>();
    int occupiedSeats5 = getNum<int>(0, maxCapacity5); // Задаем ограничение на количество занятых мест
    wagon5.setMaxCapacity(maxCapacity5);
    wagon5.setOccupiedSeats(occupiedSeats5);
    wagon5.printInfo();

    // Пересадка пассажиров
    wagon5.transferPassengers(wagon4);

    std::cout << "Wagon 4 info after passenger transfer:" << std::endl;
    wagon4.printInfo();
    std::cout << "Wagon 5 info after passenger transfer:" << std::endl;
    wagon5.printInfo();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}