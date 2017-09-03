#include "Depart.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords Depart::coordsMsg			= Coords(0, 0, 500, 500); //Random numbers
Coords Depart::coordsMsgSearchArea	= Coords(0, 0, 500, 500);

int Depart::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 3 / 10;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 169 / 200;
	int y2 = y1 + FFapp::coords.GetHeight() / 15;

	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);


	x1 = coordsMsg.GetX1() + FFapp::coords.GetWidth() * 0.08;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = coordsMsg.GetY1() + FFapp::coords.GetHeight() * 0.015;
	y2 = y1 + FFapp::coords.GetHeight() / 23;

	coordsMsgSearchArea.SetX(x1, x2);
	coordsMsgSearchArea.SetY(y1, y2);

	return 0;
}

bool Depart::IsMsg()
{
	int x1 = coordsMsg.GetAbsX1();
	int y1 = coordsMsg.GetAbsY1();
	int x2 = coordsMsg.GetAbsX2();
	int y2 = coordsMsg.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_DEPART, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int Depart::ClickBtnDepart()
{
	return MouseLeftClick(coordsMsg.GetAbsMidX(), coordsMsg.GetAbsMidY());
}

int Depart::ClickDepart()
{
	if (IsMsg())
	{
		if (ClickBtnDepart() == 0)
		{
			return WaitClass::Wait(3000);
		}
	}
	return -1;
}
