#include "Attack.h"

#include <Windows.h>

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords Attack::coordsMsg				= Coords(0, 0, 500, 500); //Random numbers
Coords Attack::coordsMsgSearchArea		= Coords(0, 0, 500, 500);
Coords Attack::coordsBtnRepeat			= Coords(0, 0, 500, 500);
std::vector<Coords> Attack::coordsChars	= std::vector<Coords>();

int Attack::DetermineLocation()
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

	coordsBtnRepeat.SetX(x1, x2);
	coordsBtnRepeat.SetY(y1, y2);

	coordsChars.clear();
	for (int i = 0; i < 6; ++i)
	{
		if ( i % 2 == 0)
		{
			x1 = coordsMsg.GetX1() + FFapp::coords.GetWidth() / 20;
			x2 = FFapp::coords.GetX1() * 3 / 2 - x1 + FFapp::coords.GetX2() / 2;
			y1 = coordsMsg.GetY1() + FFapp::coords.GetHeight() * 0.315;
			y2 = y1 + FFapp::coords.GetHeight() / 20;
		}
		else
		{
			x1 = FFapp::coords.GetX1() - coordsChars[i - 1].GetX2() + FFapp::coords.GetX2();
			x2 = FFapp::coords.GetX1() - coordsChars[i - 1].GetX1() + FFapp::coords.GetX2();
			y1 = coordsChars[i - 1].GetY1();
			y2 = coordsChars[i - 1].GetY2();
		}
		coordsChars.push_back(Coords(x1, y1, x2, y2));
	}
	

	return 0;
}

bool Attack::IsMsg()
{
	return IsRepeat() || IsRepeatDisabled();
}

bool Attack::IsRepeat()
{
	int x1 = coordsMsgSearchArea.GetAbsX1();
	int y1 = coordsMsgSearchArea.GetAbsY1();
	int x2 = coordsMsgSearchArea.GetAbsX2();
	int y2 = coordsMsgSearchArea.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_REPEAT, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}
   
bool Attack::IsRepeatDisabled()
{
	int x1 = coordsMsgSearchArea.GetAbsX1();
	int y1 = coordsMsgSearchArea.GetAbsY1();
	int x2 = coordsMsgSearchArea.GetAbsX2();
	int y2 = coordsMsgSearchArea.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_REPEAT_DISABLED, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int Attack::ClickBtnRepeat()
{
	return MouseLeftClick(coordsBtnRepeat.GetAbsMidX(), coordsBtnRepeat.GetAbsMidY());
}

int Attack::ClickChars(const int timeBetweenClicksMiliSeconds)
{
	if (coordsChars.empty()) return -1;

	int i = 0;
	int res = MouseLeftClick(coordsChars[i].GetAbsMidX(), coordsChars[i].GetAbsMidY());

	while (++i < 6 && res == 0)
	{
		Sleep(timeBetweenClicksMiliSeconds);
		res = MouseLeftClick(coordsChars[i].GetAbsMidX(), coordsChars[i].GetAbsMidY());
	};

	return res;
}

int Attack::WaitAttack()
{
	return WaitClass::WaitClickableObject(IsMsg);
}

int Attack::ClickAttack()
{
	int ret = -1;
	bool clickChars = true;

	do
	{
		if (IsRepeatDisabled())
		{
			ret = WaitClass::Wait(200);
		}
		else if (IsRepeat())
		{
			ret = ClickBtnRepeat();
			if (clickChars && ret == 0)
			{
				Sleep(200);
				ret = ClickChars();
				clickChars = false;
			}
			if (ret == 0)
				ret = WaitClass::Wait(1000);
		}
		else
		{
			break;
		}
	} while (ret == 0);

	return ret;
}
