#pragma once

#include "Coords.h"

public class Missions
{
public:
	static int DetermineLocation();
	static int ClickMissions();

private:
	static bool IsMsg();
	static int ClickBtnNext();

	static Coords coordsSearchArea;
	static Coords coordsBtnNext;
};