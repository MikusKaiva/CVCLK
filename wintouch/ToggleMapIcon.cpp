#include "ToggleMapIcon.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords ToggleMapIcon::coords = Coords(0, 0, 500, 500); //Random numbers

int ToggleMapIcon::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

	coords.SetX(x1, x2);
	coords.SetY(y1, y2);

	return 0;
}

bool ToggleMapIcon::IsMsg()
{
	int x1 = coords.GetAbsX1();
	int y1 = coords.GetAbsY1();
	int x2 = coords.GetAbsX2();
	int y2 = coords.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_MAP_ICON, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int ToggleMapIcon::ClickMapIcon()
{
	return MouseLeftClick(coords.GetAbsMidX(), coords.GetAbsMidY());
}

int ToggleMapIcon::WaitToggleMapIcon()
{
	return WaitClass::WaitClickableObject(IsMsg);
}

/*  
S . . # #
# . . . C
# . # # .
. . # # .
# . # . .
# . # # #
# . # # G
# . . . .
*/
