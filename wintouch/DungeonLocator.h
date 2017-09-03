#pragma once
#include <vector>
#include "Coords.h"


class DungeonLocator
{
public:
	static int DetermineLocation();
	static bool IsDung(std::string dungName);
	static int ClickLastDung();

private:
	static std::vector<Coords> coords;
	static int coordIndex;
};

