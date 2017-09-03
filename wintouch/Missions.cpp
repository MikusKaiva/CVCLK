#include "Missions.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"

Coords Missions::coordsSearchArea		= Coords(0, 0, 500, 500, 0, 0); //Random numbers
Coords Missions::coordsBtnNext			= Coords(0, 0, 500, 500, 0, 0);

int Missions::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 3 / 10;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() / 4;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsSearchArea.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsSearchArea.SetX(x1, x2);
	coordsSearchArea.SetY(y1, y2);


	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 4 / 10;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 17 / 20;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsBtnNext.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsBtnNext.SetX(x1, x2);
	coordsBtnNext.SetY(y1, y2);

	return 0;
}

bool Missions::IsMsg()
{
	int x1 = coordsSearchArea.GetAbsX1();
	int y1 = coordsSearchArea.GetAbsY1();
	int x2 = coordsSearchArea.GetAbsX2();
	int y2 = coordsSearchArea.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_MISSIONS_NEXT, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int Missions::ClickBtnNext()
{
	return MouseLeftClick(coordsBtnNext.GetAbsMidX(), coordsBtnNext.GetAbsMidY());
}
