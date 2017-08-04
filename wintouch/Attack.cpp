#include "Attack.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"

Coords Attack::coordsMsg			= Coords(0, 0, 500, 500, 0, 0); //Random numbers
Coords Attack::coordsMsgSearchArea	= Coords(0, 0, 500, 500, 0, 0);
Coords Attack::coordsBtnDepart		= Coords(0, 0, 500, 500, 0, 0);

int Attack::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsg.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);


	x1 = coordsMsg.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	y1 = coordsMsg.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsgSearchArea.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsMsgSearchArea.SetX(x1, x2);
	coordsMsgSearchArea.SetY(y1, y2);


	x1 = coordsMsg.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = coordsMsg.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsBtnDepart.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsBtnDepart.SetX(x1, x2);
	coordsBtnDepart.SetY(y1, y2);

	return 0;
}

bool Attack::IsMsg()
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

int Attack::ClickBtnDepart()
{
	return MouseLeftClick(coordsBtnDepart.GetAbsMidX(), coordsBtnDepart.GetAbsMidY());
}
