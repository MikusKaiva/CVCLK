#pragma once

#include <string>
#include "Coords.h"

public class WorldMap
{
public:
	int LocateDung(std::string name);
	static int DetermineLocation();
	static Coords coords;
};
