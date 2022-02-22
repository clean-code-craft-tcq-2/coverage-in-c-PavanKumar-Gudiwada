#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string.h>
#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits case low") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits case high") {
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limits case normal") {
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("set limits according cooling type") {
 	Limits limitValues;
  
  	limitValues = setLimits(PASSIVE_COOLING);
	REQUIRE(limitValues.lowerLimit == 0);
	REQUIRE(limitValues.upperLimit == 35);
	
	limitValues = setLimits(HI_ACTIVE_COOLING);
	REQUIRE(limitValues.lowerLimit == 0);
	REQUIRE(limitValues.upperLimit == 45);
	
	limitValues = setLimits(MED_ACTIVE_COOLING);
	REQUIRE(limitValues.lowerLimit == 0);
	REQUIRE(limitValues.upperLimit == 40);
	
	limitValues = setLimits((CoolingType)3);//undefined cooling type
}

TEST_CASE("classify type of breach (high/low/normal)") {
  assert(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
}

TEST_CASE("check, classify breach and send alert based on target") {
  	BatteryCharacter batteryDescription;
  
  	strcpy(batteryDescription.brand, "Excide");
	batteryDescription.coolingType = HI_ACTIVE_COOLING;
	checkAndAlert(TO_CONTROLLER,batteryDescription, 49.0);
	
	strcpy(batteryDescription.brand, "Amaron");
	batteryDescription.coolingType = PASSIVE_COOLING;
	checkAndAlert(TO_EMAIL, batteryDescription, 36.0);
	
	strcpy(batteryDescription.brand, "Amaron");
	batteryDescription.coolingType = PASSIVE_COOLING;
	checkAndAlert(TO_EMAIL, batteryDescription, -10.0);
	
	strcpy(batteryDescription.brand, "Amaron");
	batteryDescription.coolingType = PASSIVE_COOLING;
	checkAndAlert(TO_EMAIL, batteryDescription, 25.0);//normal range
}
