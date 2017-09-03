#include "ResultsGil.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"

Coords ResultsGil::coordsMsg		= Coords(0, 0, 500, 500, 0, 0); //Random numbers
Coords ResultsGil::coordsNextBtn	= Coords(0, 0, 500, 500, 0, 0);

int ResultsGil::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 4;
	int x2 = x1 + +FFapp::coords.GetWidth() / 4;
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 19 / 50;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

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

bool ResultsGil::IsMsg()
{
	int x1 = coordsMsg.GetAbsX1();
	int y1 = coordsMsg.GetAbsY1();
	int x2 = coordsMsg.GetAbsX2();
	int y2 = coordsMsg.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_RESULTS_GIL, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int ResultsGil::ClickResultsGil()
{
	return MouseLeftClick(coordsMsg.GetAbsMidX(), coordsMsg.GetAbsMidY());
}

int ResultsGil::ClickNextBtn()
{
	return MouseLeftClick(coordsNextBtn.GetAbsMidX(), coordsNextBtn.GetAbsMidY());
}
