#include "typewise-alert.h"

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

	Limits limitValues;
	limitValues = setLimits(coolingType);

  return inferBreach(temperatureInC, limitValues.lowerLimit, limitValues.upperLimit);
}
