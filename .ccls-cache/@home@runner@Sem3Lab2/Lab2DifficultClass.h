#include "Wagon.h" // Включаем заголовочный файл класса Вагон

namespace lab2ComplexClass {

    const int MAX_WAGONS = 10; // Максимальное количество вагонов в поезде

    class Train {
    private:
        Wagon wagons[MAX_WAGONS]; // Массив вагонов
        int numWagons; // Текущее количество вагонов в поезде

    public:
        // Конструктор по умолчанию
        Train();

        // Конструктор с инициализацией вагонов из массива
        explicit Train(const Wagon wagons[], int numWagons);

        // Конструктор с инициализацией одним вагоном
        explicit Train(const Wagon& wagon);

        // Метод для добавления вагона к поезду
        void addWagon(const Wagon& wagon);

        // Метод для пересадки пассажиров из одного вагона в другой
        void transferPassengers(int fromWagonIndex, int toWagonIndex);

        // Другие методы по работе с поездом (под вашу реализацию)

    };
} // namespace lab2ComplexClass