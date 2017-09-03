#pragma once

#include "Coords.h"

public class ResultsGil
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int WaitResults();
	static int ClickResultsGil();

private:
	static int ClickResultsGilMsg();
	static int ClickNextBtn();

	static Coords coordsMsg;
	static Coords coordsNextBtn;
};