#ifndef LAB2PRIMARYCLASS_H
#define LAB2PRIMARYCLASS_H

#include <iostream>
#include <stdexcept>
#include <limits>
#include <string>
#include <cstring>

namespace lab2PrimaryClass {
    
    // шаблонная функция ввода одного числа
    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) { // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            }
            else if(std::cin.bad()) { // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            }
            else if(std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if(a >= min && a <= max) { // если число входит в заданный диапазон
                return a;
            }
            else {
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

            // Вспомогательная функция для вычисления разницы в занятости вагонов
            double calculateOccupancyDifference(const Wagon& otherWagon) const {
                double occupancyPercentageThis = static_cast<double>(occupiedSeats) / maxCapacity;
                double occupancyPercentageOther = static_cast<double>(otherWagon.getOccupiedSeats()) / otherWagon.getMaxCapacity();
                return std::abs(occupancyPercentageThis - occupancyPercentageOther);
            }

        public:
            Wagon();
            Wagon(int maxCapacity, int occupiedSeats, WagonType type);
            Wagon(WagonType type);

            double getOccupancyPercentage() const;

            void boardPassengers(int passengers);
            void disembarkPassengers(int passengers);

            int getMaxCapacity() const;
            int getOccupiedSeats() const;
            WagonType getType() const;

            void setMaxCapacity(int capacity);
            void setOccupiedSeats(int seats);
            void setType(WagonType wagonType);

            void printInfo() const;

            void transferPassengers(Wagon& otherWagon);
    };
}

#endif // LAB2PRIMARYCLASS_H