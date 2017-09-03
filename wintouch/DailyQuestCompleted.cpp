#include "DailyQuestCompleted.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Wait.h"

Coords DailyQuestCompleted::coordsMsg			= Coords(0, 0, 500, 500); //Random numbers
Coords DailyQuestCompleted::coordsMsgSearchArea	= Coords(0, 0, 500, 500);
Coords DailyQuestCompleted::coordsBtnClose			= Coords(0, 0, 500, 500);

int DailyQuestCompleted::DetermineLocation()
{
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 23 / 100;
	int y2 = y1 + FFapp::coords.GetHeight() * 12 / 25;

	coordsMsg.SetX(x1, x2);
	coordsMsg.SetY(y1, y2);


	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 4;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 13 / 50;
	y2 = y1 + FFapp::coords.GetHeight() * 7 / 200;

	coordsMsgSearchArea.SetX(x1, x2);
	coordsMsgSearchArea.SetY(y1, y2);


	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() * 3 / 20;
	x2 = x1 + FFapp::coords.GetWidth()  * 11 / 50;
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 3 / 5;
	y2 = y1 + FFapp::coords.GetHeight() / 25;

	coordsBtnClose.SetX(x1, x2);
	coordsBtnClose.SetY(y1, y2);

	return 0;
}

int DailyQuestCompleted::ClickDailyQuestCompleted()
{
	if (IsMsg())
	{
		if (ClickBtnClose() == 0)
		{
			return WaitClass::Wait(1000);
		}
	}
	return -1;
}

bool DailyQuestCompleted::IsMsg()
{
	int x1 = coordsMsgSearchArea.GetAbsX1();
	int y1 = coordsMsgSearchArea.GetAbsY1();
	int x2 = coordsMsgSearchArea.GetAbsX2();
	int y2 = coordsMsgSearchArea.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_DAILY_QUEST, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int DailyQuestCompleted::ClickBtnClose()
{
	return MouseLeftClick(coordsBtnClose.GetAbsMidX(), coordsBtnClose.GetAbsMidY());
}
