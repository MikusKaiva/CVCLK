#pragma once

#include "Coords.h"

public class ResultsItems
{
public:
	static int DetermineLocation();
	static int ClickResultsItems();

private:
	static bool IsMsg();
	static int ClickResultsItemsMsg();
	static int ClickNextBtn();

	static Coords coordsMsg;
	static Coords coordsNextBtn;
};