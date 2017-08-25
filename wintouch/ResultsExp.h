#pragma once

#include "Coords.h"

public class ResultsExp
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickResultsExp();

private:
	static Coords coords;
};