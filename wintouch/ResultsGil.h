#pragma once

#include "Coords.h"

public class ResultsGil
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickResultsGil();
	static int ClickNextBtn();

private:
	static Coords coordsMsg;
	static Coords coordsNextBtn;
};