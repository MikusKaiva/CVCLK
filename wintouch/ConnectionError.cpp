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
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 10;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 75 / 200;
	int y2 = y1 + FFapp::coords.GetHeight() * 7 / 25;

	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);


	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 33 / 100;
	x2 = x1 + FFapp::coords.GetWidth()  * 7 / 20;
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 41 / 100;
	y2 = y1 + FFapp::coords.GetHeight() / 30;

	coordsMsgSearchArea.SetX(x1, x2);
	coordsMsgSearchArea.SetY(y1, y2);


	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 9 / 25;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 11 / 20;
	y2 = y1 + FFapp::coords.GetHeight() / 19;

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
	int x1 = coordsMsgSearchArea.GetAbsX1();
	int y1 = coordsMsgSearchArea.GetAbsY1();
	int x2 = coordsMsgSearchArea.GetAbsX2();
	int y2 = coordsMsgSearchArea.GetAbsY2();

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
