#include "ConnectionError.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords ConnectionError::coordsMsg			= Coords(0, 0, 500, 500); //Random numbers
Coords ConnectionError::coordsMsgSearchArea	= Coords(0, 0, 500, 500);
Coords ConnectionError::coordsBtnOk			= Coords(0, 0, 500, 500);

int ConnectionError::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);


	x1 = coordsMsg.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	y1 = coordsMsg.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsMsgSearchArea.SetX(x1, x2);
	coordsMsgSearchArea.SetY(y1, y2);


	x1 = coordsMsg.GetX1() + FFapp::coords.GetWidth() / 20;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = coordsMsg.GetY1() + FFapp::coords.GetHeight() * 0.315;
	y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsBtnOk.SetX(x1, x2);
	coordsBtnOk.SetY(y1, y2);

	return 0;
}


int ConnectionError::ClickConnectionError()
{
	if (IsMsg())
	{
		if (ClickBtnOk() == 0)
		{
			return WaitClass::Wait(3000);
		}
	}
	return -1;
}

bool ConnectionError::IsMsg()
{
	int x1 = coordsMsg.GetAbsX1();
	int y1 = coordsMsg.GetAbsY1();
	int x2 = coordsMsg.GetAbsX2();
	int y2 = coordsMsg.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_CONNECTION_ERR, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int ConnectionError::ClickBtnOk()
{
	return MouseLeftClick(coordsBtnOk.GetAbsMidX(), coordsBtnOk.GetAbsMidY());
}
