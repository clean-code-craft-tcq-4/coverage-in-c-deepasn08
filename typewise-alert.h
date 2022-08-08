#pragma once
#include <stdio.h>

#define DEFAULT_UPPERLIMIT 0
#define COOLING_LOWLIMIT 0
#define PASSIVECOOLING_UPPERLIMIT  35
#define ACTIVECOOLING_UPPERLIMIT 45
#define MED_ACTIVECOOLING_UPPERLIMIT 40

#define header 0xfeed
#define recepient "a.b@c.com"

#define LOW_TEMPWARN "Hi, the temperature is too low"
#define HIGH_TEMPWARN "Hi, the temperature is too high"

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
