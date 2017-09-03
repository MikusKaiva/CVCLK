#include "NoCompanion.h"

#include "FFapp.h"
#include "constants.h"
#include "FindImage.h"
#include "MouseControl.h"

Coords NoCompanion::coordsSearchArea	= Coords(0, 0, 500, 500, 0, 0); //Random numbers
Coords NoCompanion::coordsBtnNoCompanion = Coords(0, 0, 500, 500, 0, 0);

int NoCompanion::DetermineLocation()
{
	int x1 = FFapp::coords.GetX2() - FFapp::coords.GetWidth() / 30;
	int x2 = FFapp::coords.GetX2();
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 61 / 200;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;

	coordsSearchArea.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsSearchArea.SetX(x1, x2);
	coordsSearchArea.SetY(y1, y2);


	x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 35;
	x2 = FFapp::coords.GetX1() - x1 + FFapp::coords.GetX2();
	y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 87 / 100;
	y2 = y1 + FFapp::coords.GetHeight() / 8;

	coordsBtnNoCompanion.SetOffset(FFapp::coords.GetOffsetX(), FFapp::coords.GetOffsetY());
	coordsBtnNoCompanion.SetX(x1, x2);
	coordsBtnNoCompanion.SetY(y1, y2);

	return 0;
}

bool NoCompanion::IsSlider()
{
	int x1 = coordsSearchArea.GetAbsX1();
	int y1 = coordsSearchArea.GetAbsY1();
	int x2 = coordsSearchArea.GetAbsX2();
	int y2 = coordsSearchArea.GetAbsY2();

	if (FindImageInPartOfDesktop(IMG_SLIDER, x1, y1, x2, y2) == 0)
	{
		return true;
	}

	return false;
}

int NoCompanion::ClickNoCompanion()
{
	int ret = -1;

	int prevX, prevY;
	bool prevPositionsaved = false;
	if (GetMousePosition(prevX, prevY) == 0)
		prevPositionsaved = true;

	ret = SetMousePosition(coordsSearchArea.GetAbsMidX(), coordsSearchArea.GetAbsMidY());

	if (ret == 0)
	{
		ret = MouseLeftDown();
	}

	if (ret == 0)
	{
		ret = MoveMouseTo(coordsSearchArea.GetAbsMidX(), coordsSearchArea.GetAbsMidY() + FFapp::coords.GetHeight() * 0.61, 500);
	}

	if (ret == 0)
	{
		ret = MouseLeftUp();
	}

	if (ret == 0)
	{
		MouseLeftClick(coordsBtnNoCompanion.GetAbsMidX(), coordsBtnNoCompanion.GetAbsMidY());
	}
	if (prevPositionsaved)
		SetMousePosition(prevX, prevY);

	return ret;
}
