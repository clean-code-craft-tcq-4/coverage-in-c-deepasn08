#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowerLimit = COOLING_LOWLIMIT;
  int upperLimit = 0;
  if(coolingType == PASSIVE_COOLING )
      upperLimit = PASSIVECOOLING_UPPERLIMIT;
   else if (coolingType == HI_ACTIVE_COOLING)
      upperLimit = ACTIVECOOLING_UPPERLIMIT;
   else if (coolingType == MED_ACTIVE_COOLING)
      upperLimit = MED_ACTIVECOOLING_UPPERLIMIT;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  if (alertTarget == TO_CONTROLLER )
      sendToController(breachType);
  else if (alertTarget == TO_EMAIL)
      sendToEmail(breachType);
  }

void sendToController(BreachType breachType) {
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
   if (breachType==TOO_LOW)
      printf("To: %s\n %s\n", recepient,LOW_TEMPWARN );
   else if (breachType == TOO_HIGH)
      printf("To: %s\n %s\n", recepient,HIGH_TEMPWARN );

}
