#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(-10, COOLING_LOWLIMIT, PASSIVECOOLING_UPPERLIMIT) == TOO_LOW);
  REQUIRE(inferBreach(45, COOLING_LOWLIMIT, PASSIVECOOLING_UPPERLIMIT) == TOO_HIGH);
  REQUIRE(inferBreach(25, COOLING_LOWLIMIT, PASSIVECOOLING_UPPERLIMIT) == NORMAL);
  REQUIRE(inferBreach(-8, COOLING_LOWLIMIT, ACTIVECOOLING_UPPERLIMIT) == TOO_LOW );
  REQUIRE(inferBreach(55, COOLING_LOWLIMIT, ACTIVECOOLING_UPPERLIMIT) == TOO_HIGH);
  REQUIRE(inferBreach(28, COOLING_LOWLIMIT, ACTIVECOOLING_UPPERLIMIT) ==  NORMAL);
  REQUIRE(inferBreach(-3, COOLING_LOWLIMIT, MED_ACTIVECOOLING_UPPERLIMIT) == TOO_LOW);
  REQUIRE(inferBreach(56, COOLING_LOWLIMIT, MED_ACTIVECOOLING_UPPERLIMIT) == TOO_HIGH );
  REQUIRE(inferBreach(25, COOLING_LOWLIMIT, MED_ACTIVECOOLING_UPPERLIMIT) == NORMAL);
}


TEST_CASE("classify temperature breach"){
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-10)== TOO_LOW);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,45)== TOO_HIGH);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,25)== NORMAL);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-8)== TOO_LOW);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,55)== TOO_HIGH);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,28)== NORMAL);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-3)== TOO_LOW);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,56)== TOO_HIGH);
 REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,25)== NORMAL);
}

TEST_CASE("check and alert"){
  BatteryCharacter batteryparameter ;
  batteryparameter.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryparameter,-10);
  checkAndAlert(TO_EMAIL,batteryparameter,45);
  checkAndAlert(TO_EMAIL,batteryparameter,25);

  batteryparameter.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryparameter,-8);
  checkAndAlert(TO_EMAIL,batteryparameter,55);
  checkAndAlert(TO_EMAIL,batteryparameter,28);

  batteryparameter.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER,batteryparameter,-3);
  checkAndAlert(TO_EMAIL,batteryparameter,56);
  checkAndAlert(TO_EMAIL,batteryparameter,25);
}

TEST_CASE("Classification check by send controller"){
  sendToController(NORMAL);
  sendToController(TOO_LOW);
  sendToController(TOO_HIGH);
}

TEST_CASE("Classification check by send email"){
  sendToEmail(NORMAL);
  sendToEmail(TOO_LOW);
  sendToEmail(TOO_HIGH);
}