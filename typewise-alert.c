#include <stdio.h>
#include "typewise-alert.h"

breachType_t ClassifyBreach(coolingSystem_t coolingSystem, double temperatureInC)
{
	if (temperatureInC < coolingSystem.lowLimit)
	{
		return TOO_LOW;
	}
	else if (temperatureInC > coolingSystem.hiLimit)
	{
		return TOO_HIGH;
	}
	else
	{
		return NORMAL;
	}
}

void SendAlert(unsigned int target, breachType_t breachType)
{
	printf("To: %s\nTemperature is %s\n", targetMsgs[target], breachMsgs[breachType]);
}

void CheckAndAlert(batteryCharacter_t batteryChar, double temperatureInC)
{
	breachType_t breachType = ClassifyBreach(batteryChar.battCoolingSystem, temperatureInC);

	SendAlert(batteryChar.target, breachType);
}