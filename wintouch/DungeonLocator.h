#pragma once
#include <vector>
#include "Coords.h"


class DungeonLocator
{
public:
	static int DetermineLocation();
	static int ClickEarthShrine_Exit();

private:
	static bool IsDung(std::string dungName);
	static int ClickLastDung();
	static int ClickDung(std::string dungName);

	static std::vector<Coords> coords;
	static int coordIndex;
};

