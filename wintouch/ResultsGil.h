#pragma once

#include "Coords.h"

public class ResultsGil
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickResultsGil();

private:
	static Coords coords;
};