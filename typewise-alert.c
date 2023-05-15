#include <stdio.h>
#include "typewise-alert.h"

const coolingSystem_t coolingSystems[COOLING_TYPE_COUNT] = {
	[PASSIVE_COOLING] =		{ .lowLimit = 0.0F,	.hiLimit = 35.0F },
	[HI_ACTIVE_COOLING] =	{ .lowLimit = 0.0F,	.hiLimit = 45.0F },
	[MED_ACTIVE_COOLING] =	{ .lowLimit = 0.0F,	.hiLimit = 40.0F }
};

char breachMsgs[2][20] = {
	"too low",
	"too high"
};

char targetMsgs[2][30] = {
	"Controller",
	"mail@domain.com"
};

char alertMsg[70] = " ";

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
	sprintf(alertMsg, "To: %s\nTemperature is %s\n", targetMsgs[target], breachMsgs[breachType - 1]);
	printf(alertMsg);
}

void CheckAndAlert(const batteryCharacter_t batteryChar, const double temperatureInC)
{
	const breachType_t breachType = ClassifyBreach(batteryChar.battCoolingSystem, temperatureInC);

	if ((breachType != NORMAL))
	{
		SendAlert(batteryChar.target, breachType);
	}
}

//Added for local compiling
/*int main()
{
	SendAlert(TO_CONTROLLER, TOO_LOW);

	SendAlert(TO_CONTROLLER, TOO_HIGH);

	SendAlert(TO_EMAIL, TOO_LOW);

	SendAlert(TO_EMAIL, TOO_HIGH);

	return 0;
}*/