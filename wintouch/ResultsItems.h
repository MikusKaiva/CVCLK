#pragma once

#include "Coords.h"

public class ResultsItems
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickResultsItems();
	static int ClickNextBtn();

private:
	static Coords coordsMsg;
	static Coords coordsNextBtn;
};