#include "ResultsGil.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords ResultsGil::coordsMsg		= Coords(0, 0, 500, 500); //Random numbers
Coords ResultsGil::coordsNextBtn	= Coords(0, 0, 500, 500);

int ResultsGil::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);

	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

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

int ResultsGil::ClickResultsGilMsg()
{
	return MouseLeftClick(coordsMsg.GetAbsMidX(), coordsMsg.GetAbsMidY());
}

int ResultsGil::ClickNextBtn()
{
	return MouseLeftClick(coordsNextBtn.GetAbsMidX(), coordsNextBtn.GetAbsMidY());
}

int ResultsGil::WaitResults()
{
	return WaitClass::WaitClickableObject(IsMsg);
}

int ResultsGil::ClickResultsGil()
{
	int ret = -1;
	if (IsMsg())
	{
		int i = 0;
		do
		{
			ret = ClickResultsGilMsg();
			if (ret == 0) ret = WaitClass::Wait(500);
		} while (ret == 0 && ++i <= 3);

		if (ret == 0)
		{
			ClickNextBtn();
		}

		if (ret == 0)
		{
			ret = WaitClass::Wait(1000);
		}
	}
	return ret;
}
