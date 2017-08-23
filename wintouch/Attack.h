#pragma once

#include <vector>
#include "Coords.h"

public class Attack
{
public:
	static int DetermineLocation();
	static bool IsRepeat();
	static bool IsRepeatDisabled();
	static int ClickBtnRepeat();
	static int ClickChars(const int timeBetweenClicksMiliSeconds = 50);

private:
	static Coords coordsMsg;
	static Coords coordsMsgSearchArea;
	static Coords coordsBtnRepeat;
	static std::vector<Coords> coordsChars;
};