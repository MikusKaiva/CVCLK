#pragma once

#include "Coords.h"

public class ResultsExp
{
public:
	static int DetermineLocation();
	static int ClickResultsExp();

private:
	static bool IsMsg();
	static int ClickResultsExpMsg();

	static Coords coords;
};