#include "ResultsExp.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords ResultsExp::coords = Coords(0, 0, 500, 500); //Random numbers

int ResultsExp::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 7 / 25;
	int x2 = x1 + FFapp::coords.GetWidth() * 11 / 50;
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 23 / 200;
	int y2 = y1 + FFapp::coords.GetHeight() * 3 / 100;

	coords.SetX(x1, x2);
	coords.SetY(y1, y2);

	return 0;
}

bool ResultsExp::IsMsg()
{
	int x1 = coords.GetAbsX1();
	int y1 = coords.GetAbsY1();
	int x2 = coords.GetAbsX2();
	int y2 = coords.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_RESULTS_EXP, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int ResultsExp::ClickResultsExpMsg()
{
	return MouseLeftClick(coords.GetAbsMidX(), coords.GetAbsMidY());
}

int ResultsExp::ClickResultsExp()
{
	int ret = -1;
	if (IsMsg())
	{
		if (ClickResultsExpMsg() == 0)
		{
			return WaitClass::Wait(1000);
		}
	}
	return -1;
}
