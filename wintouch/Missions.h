#pragma once

#include "Coords.h"

public class Missions
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickBtnNext();

private:
	static Coords coordsSearchArea;
	static Coords coordsBtnNext;
};