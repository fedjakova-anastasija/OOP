#include "stdafx.h"
//#include "../TV/CTVSet.h"
//#include "../TV/RemoteControl.h"
#include "../TV/CTVSet.cpp"

TEST_CASE("Translation of a new word is added to the dictionary", "[SelectChannel]")
{
	CTVSet tvSet;
	CHECK(tvSet.SelectChannel(1) == false);
	CHECK(tvSet.GetSelectedChannel() == 0);
}