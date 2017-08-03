#include "Energy.h"

#include "FFapp.h"

int Energy::DetermineLocation()
{

	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth() / 20;
	int x2 = x1 + FFapp::coords.GetWidth()  * 0.73;
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;
	int offsetX = FFapp::coords.GetOffsetX();
	int offsetY = FFapp::coords.GetOffsetY();
	coords = Coords(x1, y1, x2, y2, offsetX, offsetY);

	//int spaceBetween = FFapp::coords.GetHeight() * 0.148;
	//for (int i = 0; i < 4; ++i)
	//{
	//	y1 += spaceBetween;
	//	y2 += spaceBetween;
	//	coords.push_back(Coords(x1, y1, x2, y2, offsetX, offsetY));
	//}

	return 0;
}