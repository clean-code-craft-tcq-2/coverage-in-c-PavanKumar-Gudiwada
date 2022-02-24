#include "typewise-alert.h"
#include "sendToTargets.h"

Limits coolingMethodLimitValues[3] = {{0,35}, {0,45}, {0,40}};

Limits setLimits(CoolingType coolingType)
{
	Limits limitValues;
	
	limitValues = coolingMethodLimitValues[(int)coolingType];
	
  return limitValues;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

	// sendToTarget is an array of function pointers
    void (*sendToTarget[])(BreachType) = {&sendToController, &sendToEmail};

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  (*sendToTarget[alertTarget])(breachType);
  
}
