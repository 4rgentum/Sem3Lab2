#include <iostream>
#include <string>

class Wagon {
private:
    int maxCapacity;
    int occupiedSeats;
    std::string type;

public:
    // Конструктор для инициализации максимальной вместимости, количества занятых мест и типа
    Wagon(int capacity, int seats, const std::string& wagonType) : maxCapacity(capacity), occupiedSeats(seats), type(wagonType) {
        if (type == "ресторан") {
            maxCapacity = 0; // Вместимость ресторанного вагона всегда 0
            occupiedSeats = 0; // Нельзя забронировать место в ресторане
        }
    }

    // Конструктор для инициализации только типа
    Wagon(const std::string& wagonType) : type(wagonType) {
        if (type == "сидячий") {
            maxCapacity = 50; // Вместимость сидячего вагона
            occupiedSeats = 0;
        } else if (type == "эконом") {
            maxCapacity = 40; // Вместимость эконом-класса
            occupiedSeats = 0;
        } else if (type == "люкс") {
            maxCapacity = 20; // Вместимость вагона люкс-класса
            occupiedSeats = 0;
        } else if (type == "ресторан") {
            maxCapacity = 0; // Вместимость ресторанного вагона всегда 0
            occupiedSeats = 0; // Нельзя забронировать место в ресторане
        }
    }

    // Получить процент занятости вагона
    double getOccupancyPercentage() const {
        if (maxCapacity == 0) {
            return 0; // Ресторанный вагон всегда 0% заполнен
        }
        return static_cast<double>(occupiedSeats) / maxCapacity * 100.0;
    }

    // Переместить пассажиров из одного вагона в другой
    void movePassengersTo(Wagon& otherWagon) {
        double occupancyPercentage1 = getOccupancyPercentage();
        double occupancyPercentage2 = otherWagon.getOccupancyPercentage();

        // Вычисляем, сколько пассажиров нужно переместить, чтобы уровень занятости был ближе к равномерному
        int passengersToMove = static_cast<int>((occupancyPercentage1 - occupancyPercentage2) / 2.0);

        // Проверяем, есть ли место для перемещения пассажиров
        int remainingSeats1 = maxCapacity - occupiedSeats;
        int remainingSeats2 = otherWagon.maxCapacity - otherWagon.occupiedSeats;

        if (passengersToMove > 0 && passengersToMove <= remainingSeats1 && passengersToMove <= remainingSeats2) {
            occupiedSeats -= passengersToMove;
            otherWagon.occupiedSeats += passengersToMove;
        } else {
            std::cout << "Невозможно выполнить перемещение пассажиров." << std::endl;
        }
    }

    // Посадить заданное число пассажиров в вагон
    void boardPassengers(int numPassengers) {
        int remainingSeats = maxCapacity - occupiedSeats;
        if (numPassengers <= remainingSeats) {
            occupiedSeats += numPassengers;
        } else {
            std::cout << "Недостаточно свободных мест в вагоне." << std::endl;
        }
    }

    // Высадить заданное число пассажиров из вагона
    void disembarkPassengers(int numPassengers) {
        if (numPassengers <= occupiedSeats) {
            occupiedSeats -= numPassengers;
        } else {
            std::cout << "Недостаточно пассажиров в вагоне." << std::endl;
        }
    }
};

int main() {
    // Создаем вагоны с разными характеристиками
    Wagon wagon1(50, 10, "сидячий");
    Wagon wagon2("эконом");
    Wagon wagon3("ресторан");

    // Пример использования методов
    wagon1.boardPassengers(5);
    wagon2.boardPassengers(8);

    std::cout << "Вагон 1: Процент занятости - " << wagon1.getOccupancyPercentage() << "%" << std::endl;
    std::cout << "Вагон 2: Процент занятости - " << wagon2.getOccupancyPercentage() << "%" << std::endl;
    std::cout << "Вагон 3: Процент занятости - " << wagon3.getOccupancyPercentage() << "%" << std::endl;

    wagon1.movePassengersTo(wagon2);

    std::cout << "Вагон 1: Процент занятости - " << wagon1.getOccupancyPercentage() << "%" << std::endl;
    std::cout << "Вагон 2: Процент занятости - " << wagon2.getOccupancyPercentage() << "%" << std::endl;

    wagon2.disembarkPassengers(5);

    std::cout << "Вагон 2: Процент занятости - " << wagon2.getOccupancyPercentage() << "%" << std::endl;

    return 0;
}