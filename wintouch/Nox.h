#pragma once

#include <string>
#include "Coords.h"

public class Nox
{
public:
	int Start();
	int StartApp(std::string appName);
	bool IsRunning();
	static int DetermineLocation();
	static Coords coords;
	const static int TOP_BAR_HEIGHT;
	const static int RIGHT_BAR_WIDTH;
};
