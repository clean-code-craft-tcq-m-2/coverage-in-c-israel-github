
#pragma once

typedef enum coolingType_e {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  COOLING_TYPE_COUNT
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
	double lowLimit;
	double hiLimit;
} coolingSystem_t;

typedef struct batteryCharacter_s {
  char brand[48];
  coolingSystem_t battCoolingSystem;
  alertTarget_t target;
} batteryCharacter_t;

extern coolingSystem_t coolingSystems[COOLING_TYPE_COUNT];
extern char breachMsgs[3][20];
extern char targetMsgs[2][30];

breachType_t ClassifyBreach(coolingSystem_t coolingSystem, double temperatureInC);
void SendAlert(unsigned int target, breachType_t breachType);
void CheckAndAlert(batteryCharacter_t batteryChar, double temperatureInC);