
#pragma once

typedef enum coolingType_e {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} coolingType_t;

typedef enum breachType_e {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} breachType_t;

typedef enum alertTarget_e {
  TO_CONTROLLER,
  TO_EMAIL
} alertTarget_t;

typedef struct coolingSystem_s {
	char name[10];
	int lowLimit;
	int hiLimit;
} coolingSystem_t;

typedef struct batteryCharacter_s {
  char brand[48];
  coolingSystem_t battCoolingSystem;
  unsigned int target;
} batteryCharacter_t;

coolingSystem_t coolingSystems[] = {
	{ .name = "Passive",	.lowLimit = 0.0F,	.hiLimit = 35.0F },
	{ .name = "Hi_Active",	.lowLimit = 0.0F,	.hiLimit = 45.0F },
	{ .name = "Med_Active",	.lowLimit = 0.0F,	.hiLimit = 40.0F }
};

char breachMsgs[3][10] = {
	"OK",
	"too low",
	"too high"
};

char targetMsgs[2][30] = {
	"Controller",
	"mail@server.com"
};

breachType_t ClassifyBreach(coolingSystem_t coolingSystem, double temperatureInC);
void SendAlert(unsigned int target, breachType_t breachType);
void CheckAndAlert(batteryCharacter_t batteryChar, double temperatureInC);