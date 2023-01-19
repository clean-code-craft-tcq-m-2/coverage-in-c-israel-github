#include <stdio.h>
#include "typewise-alert.h"

breachType_t ClassifyBreach(const coolingSystem_t coolingSystem, const double temperatureInC)
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

void SendAlert(const unsigned int target, const breachType_t breachType)
{
	printf("To: %s\nTemperature is %s\n", targetMsgs[target], breachMsgs[breachType]);
}

void CheckAndAlert(const batteryCharacter_t batteryChar, const double temperatureInC)
{
	const breachType_t breachType = ClassifyBreach(batteryChar.battCoolingSystem, temperatureInC);

	SendAlert(batteryChar.target, breachType);
}

//Added for local compiling
// void main(){}