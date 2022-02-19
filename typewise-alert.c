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
	
	if(coolingType == PASSIVE_COOLING)
	{
		limitValues.lowerLimit = 0;
      	limitValues.upperLimit = 35;
	}else if(coolingType == HI_ACTIVE_COOLING)
	{
		limitValues.lowerLimit = 0;
      	limitValues.upperLimit = 45;
	}else if(coolingType == MED_ACTIVE_COOLING)
	{
		limitValues.lowerLimit = 0;
      	limitValues.upperLimit = 40;
	}
	
  return limitValues;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {

	Limits limitValues;
	limitValues = setLimits(coolingType);

  return inferBreach(temperatureInC, limitValues.lowerLimit, limitValues.upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

	// sendToTarget is an array of function pointers
    void (*sendToTarget[])(BreachType) = {&sendToController, &sendToEmail};

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  (*sendToTarget[alertTarget])(breachType);
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
