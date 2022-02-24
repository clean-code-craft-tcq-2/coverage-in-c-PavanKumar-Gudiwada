#include "typewise-alert.h"
#include <stdio.h>

char * breachStr[] = {"low", "high"};

Limits coolingMethodLimitValues[3] = {{0,35}, {0,45}, {0,40}};

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
	
	limitValues = coolingMethodLimitValues[(int)coolingType];
	
  return limitValues;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {

	Limits limitValues;
	limitValues = setLimits(coolingType);

  return inferBreach(temperatureInC, limitValues.lowerLimit, limitValues.upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

	// sendToTarget is an array of function pointers
    void (*sendToTarget[])(BreachType) = {&sendToController, &sendToEmail, NULL};

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
