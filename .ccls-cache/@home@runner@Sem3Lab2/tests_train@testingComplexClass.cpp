#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../train/train.h"

TEST_CASE("TrainConstructor") {
    SECTION("DefaultConstructor") {
        lab2SimpleClass::Train train;
        REQUIRE(train.getNumOfWagons() == 0);
    }

    SECTION("InitConstructor") {
        lab2SimpleClass::Train train(5);
        REQUIRE(train.getNumOfWagons() == 5);
    }

    SECTION("AddWagon") {
        lab2SimpleClass::Train train;
        train.addWagon(lab2SimpleClass::WagonType::SITTING);
        REQUIRE(train.getNumOfWagons() == 1);
        REQUIRE(train.getWagon(0).getType() == lab2SimpleClass::WagonType::SITTING);
    }

    SECTION("TestException") {
        REQUIRE_THROWS(lab2SimpleClass::Train(-1));
    }
}

TEST_CASE("TrainMethods") {
    lab2SimpleClass::Train train;
    train.addWagon(lab2SimpleClass::WagonType::SITTING);
    train.addWagon(lab2SimpleClass::WagonType::ECONOMY);
    
    SECTION("GetTotalPassengerCount") {
        train.getWagon(0).boardPassengers(50);
        train.getWagon(1).boardPassengers(30);
        REQUIRE(train.getTotalPassengerCount() == 80);
    }

    SECTION("GetTotalOccupancyPercentage") {
        train.getWagon(0).boardPassengers(40);
        train.getWagon(1).boardPassengers(20);
        REQUIRE(train.getTotalOccupancyPercentage() == Approx(60.0));
    }

    SECTION("TransferPassengersBetweenWagons") {
        train.getWagon(0).boardPassengers(20);
        train.getWagon(1).boardPassengers(10);
        train.transferPassengers(0, 1);
        REQUIRE(train.getWagon(0).getOccupiedSeats() == 15);
        REQUIRE(train.getWagon(1).getOccupiedSeats() == 15);
    }
}