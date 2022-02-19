#include "typewise-alert.h"
#include <stdio.h>

char * breachStr[] = {"low", "high"};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

Limits setLimits(CoolingType coolingType)
{
	Limits limitValues;
	
	switch(coolingType) {
    case PASSIVE_COOLING:
      limitValues.lowerLimit = 0;
      limitValues.upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      limitValues.lowerLimit = 0;
      limitValues.upperLimit = 45;
      break;
    case MED_ACTIVE_COOLING:
      limitValues.lowerLimit = 0;
      limitValues.upperLimit = 40;
      break;
  }
  return limitValues;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {

	Limits limitValues;
	limitValues = setLimits(coolingType);

  return inferBreach(temperatureInC, limitValues.lowerLimit, limitValues.upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  
  if((breachType == 1)||(breachType == 2))
  {
	printf("To: %s\n", recepient);
	printf("Hi, the temperature is too %s\n", breachStr[breachType-1]);
  }
  
}
