#include "ResultsItems.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"

Coords ResultsItems::coordsMsg = Coords(0, 0, 500, 500, 0, 0); //Random numbers
Coords ResultsItems::coordsNextBtn = Coords(0, 0, 500, 500, 0, 0);

int ResultsItems::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 7 / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 23 / 200;
	int y2 = y1 + FFapp::coords.GetHeight() * 3 / 100;

	coordsMsg.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);

	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 2 / 5;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 17 / 20;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsNextBtn.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsNextBtn.SetX(x1, x2);
	coordsNextBtn.SetY(y1, y2);

	return 0;
}

bool ResultsItems::IsMsg()
{
	int x1 = coordsMsg.GetAbsX1();
	int y1 = coordsMsg.GetAbsY1();
	int x2 = coordsMsg.GetAbsX2();
	int y2 = coordsMsg.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_RESULTS_ITEMS, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int ResultsItems::ClickResultsItems()
{
	return MouseLeftClick(coordsMsg.GetAbsMidX(), coordsMsg.GetAbsMidY());
}

int ResultsItems::ClickNextBtn()
{
	return MouseLeftClick(coordsNextBtn.GetAbsMidX(), coordsNextBtn.GetAbsMidY());
}
