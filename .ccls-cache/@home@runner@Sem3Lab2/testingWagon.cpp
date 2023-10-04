#define CATCH_CONFIG_MAIN // Просит Catch2 реализовать свой main, снимая эту
                          // задачу с разработчика
#include "Wagon.h" // Включаем заголовочный файл с объявлениями классов
#include <catch2/catch.hpp>

using namespace lab2SimpleClass;

// Тестирование конструкторов
TEST_CASE("WagonConstructor") {
  SECTION("DefaultConstructor") {
    Wagon wagon;
    REQUIRE(wagon.getMaxCapacity() == 0);
    REQUIRE(wagon.getOccupiedSeats() == 0);
    REQUIRE(wagon.getType() == WagonType::RESTAURANT);
  }
  SECTION("ParametrizedConstructors") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    REQUIRE(wagon1.getMaxCapacity() == 100);
    REQUIRE(wagon1.getOccupiedSeats() == 50);
    REQUIRE(wagon1.getType() == WagonType::SITTING);

    Wagon wagon2(WagonType::ECONOMY);
    REQUIRE(wagon2.getMaxCapacity() == 50);
    REQUIRE(wagon2.getOccupiedSeats() == 0);
    REQUIRE(wagon2.getType() == WagonType::ECONOMY);
  }
  SECTION("InitConstructors") {
    Wagon wagon3(WagonType::LUXURY);
    REQUIRE(wagon3.getMaxCapacity() == 30);
    REQUIRE(wagon3.getOccupiedSeats() == 0);
    REQUIRE(wagon3.getType() == WagonType::LUXURY);

    Wagon wagon4(WagonType::RESTAURANT);
    REQUIRE(wagon4.getMaxCapacity() == 0);
    REQUIRE(wagon4.getOccupiedSeats() == 0);
    REQUIRE(wagon4.getType() == WagonType::RESTAURANT);
  }
  SECTION("TestException") {
    REQUIRE_THROWS(Wagon(-1, 0, WagonType::SITTING));
    REQUIRE_THROWS(Wagon(WagonType::RESTAURANT));
  }
}

// Тестирование других методов
TEST_CASE("WagonMethods") {
  SECTION("Setters") {
    Wagon wagon;
    wagon.setMaxCapacity(75);
    REQUIRE(wagon.getMaxCapacity() == 75);
    wagon.setOccupiedSeats(30);
    REQUIRE(wagon.getOccupiedSeats() == 30);
    wagon.setType(WagonType::ECONOMY);
    REQUIRE(wagon.getType() == WagonType::ECONOMY);
  }

  SECTION("PassengerOperations") {
    Wagon wagon(100, 50, WagonType::SITTING);
    wagon.boardPassengers(10);
    REQUIRE(wagon.getOccupiedSeats() == 60);
    wagon.disembarkPassengers(5);
    REQUIRE(wagon.getOccupiedSeats() == 55);
    // Тест на попытку посадки большего числа пассажиров, чем вмещает вагон
    REQUIRE_THROWS(wagon.boardPassengers(50));
    // Тест на попытку высадки большего числа пассажиров, чем есть в вагоне
    REQUIRE_THROWS(wagon.disembarkPassengers(60));
  }

  SECTION("TransferPassengers") {
    Wagon wagon1(100, 50, WagonType::SITTING);
    Wagon wagon2(50, 20, WagonType::ECONOMY);
    wagon1.transferPassengers(wagon2);
    REQUIRE(wagon1.getOccupiedSeats() == 45);
    REQUIRE(wagon2.getOccupiedSeats() == 25);
    // Тест на попытку пересадки пассажиров в ресторан
    Wagon wagon3(WagonType::RESTAURANT);
    REQUIRE_THROWS(wagon1.transferPassengers(wagon3));
    REQUIRE_THROWS(wagon3.transferPassengers(wagon1));
    // Тест на попытку пересадки пассажиров, когда вагон назначения заполнен
    Wagon wagon4(100, 80, WagonType::SITTING);
    REQUIRE_THROWS(wagon1.transferPassengers(wagon4));
  }
}