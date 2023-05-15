#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include "string.h"

batteryCharacter_t testBatteries[2] = {
	{.battCoolingSystem = coolingSystems[0], .target = TO_CONTROLLER},
	{.battCoolingSystem = coolingSystems[0], .target = TO_EMAIL},
	};

TEST_CASE("infers the breach according to limits") {
	REQUIRE(ClassifyBreach(coolingSystems[PASSIVE_COOLING], -12.0F) == TOO_LOW);
	REQUIRE(ClassifyBreach(coolingSystems[PASSIVE_COOLING], 12.0F) == NORMAL);
	REQUIRE(ClassifyBreach(coolingSystems[PASSIVE_COOLING], 40.0F) == TOO_HIGH);

	REQUIRE(ClassifyBreach(coolingSystems[HI_ACTIVE_COOLING], -12.0F) == TOO_LOW);
	REQUIRE(ClassifyBreach(coolingSystems[HI_ACTIVE_COOLING], 40.0F) == NORMAL);
  	REQUIRE(ClassifyBreach(coolingSystems[HI_ACTIVE_COOLING], 60.0F) == TOO_HIGH);

	REQUIRE(ClassifyBreach(coolingSystems[MED_ACTIVE_COOLING], -12.0F) == TOO_LOW);
	REQUIRE(ClassifyBreach(coolingSystems[MED_ACTIVE_COOLING], 35.0F) == NORMAL);
	REQUIRE(ClassifyBreach(coolingSystems[MED_ACTIVE_COOLING], 45.0F) == TOO_HIGH);
}

TEST_CASE("Alert messages") {
	CheckAndAlert(testBatteries[0], 12.0F);
	REQUIRE(strcmp(alertMsg, " ") == 0);

	CheckAndAlert(testBatteries[0], -12.0F);
	//SendAlert(TO_CONTROLLER, TOO_LOW);
	REQUIRE(strcmp(alertMsg, "To: Controller\nTemperature is too low\n") == 0);

	CheckAndAlert(testBatteries[0], 40.0F);
	//SendAlert(TO_CONTROLLER, TOO_HIGH);
	REQUIRE(strcmp(alertMsg, "To: Controller\nTemperature is too high\n") == 0);

	CheckAndAlert(testBatteries[1], -12.0F);
	//SendAlert(TO_EMAIL, TOO_LOW);
	REQUIRE(strcmp(alertMsg, "To: mail@domain.com\nTemperature is too low\n") == 0);

	CheckAndAlert(testBatteries[1], 40.0F);
	//SendAlert(TO_EMAIL, TOO_HIGH);
	REQUIRE(strcmp(alertMsg, "To: mail@domain.com\nTemperature is too high\n") == 0);
}
