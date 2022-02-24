#include <stdio.h>

#include "typewise-alert.h"

char * breachStr[] = {"low", "high"};

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
