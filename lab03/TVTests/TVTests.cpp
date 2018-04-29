#include "stdafx.h"
#include "../TV/CTVSet.h"
#include "../TV/RemoteControl.h"
#include "../TV/CTVSet.cpp"

TEST_CASE("TurnOn test")
{
	CTVSet tvSet;
	REQUIRE(tvSet.IsTurnedOn() == false);
	REQUIRE(tvSet.GetSelectedChannel() == 0);
}