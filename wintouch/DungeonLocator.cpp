#include "DungeonLocator.h"

#include <opencv2/opencv.hpp>

#include "FFapp.h"
#include "constants.h"
#include "Log.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "DesktopCapture.h"

using namespace cv;
using namespace std;

vector<Coords> DungeonLocator::coords = vector<Coords>();
int DungeonLocator::coordIndex = 0;

int DungeonLocator::DetermineLocation()
{
	coords.clear();
	
	int x1 = FFapp::coords.GetX1() + FFapp::coords.GetWidth()  / 20;
	int x2 = x1 + FFapp::coords.GetWidth()  * 0.73 ;
	int y1 = FFapp::coords.GetY1() + FFapp::coords.GetHeight() * 0.315 ;
	int y2 = y1 + FFapp::coords.GetHeight() / 20;
	int offsetX = FFapp::coords.GetOffsetX();
	int offsetY = FFapp::coords.GetOffsetY();
	coords.push_back(Coords(x1, y1, x2, y2, offsetX, offsetY));

	int spaceBetween = FFapp::coords.GetHeight() * 0.148;
	for (int i = 0; i < 4; ++i)
	{
		y1 += spaceBetween;
		y2 += spaceBetween;
		coords.push_back(Coords(x1, y1, x2, y2, offsetX, offsetY));
	}
	
	return 0;
}

bool DungeonLocator::IsDung(std::string dungName)
{
	string templName;
	if (dungName == E_SHRINE_EXIT)
	{
		coordIndex = 1;
		templName = IMG_E_SHRINE_EXIT;
	}
	else
	{
		LOG("No dungeon with a name: " + dungName);
		return false;
	}

	if (coords.size() <= coordIndex)
	{
		LOG("Invalid dungeon coords");
		return false;
	}

	Mat templ, src;
	int res = -1;
	int x1 = coords[coordIndex].GetAbsX1(); 
	int y1 = coords[coordIndex].GetAbsY1();
	int x2 = coords[coordIndex].GetAbsX2();
	int y2 = coords[coordIndex].GetAbsY2();

	res = GetPartOfDesktop(src,x1, y1, x2, y2);

	if (res != 0) 
		LOG("Failed to get Part Of Desktop");

	if (res == 0)
	{
		templ = imread(templName, IMREAD_COLOR);
		if (templ.empty())
		{
			LOG("Image '" + templName  + "' not found");
			res = -1;
		}
	}

	if (res == 0)
	{
		res = FindImage(templ, src, x1, y1, x2, y2);
		if (res != 0) LOG("Image not found in area");
	}

	if (res == 0)
	{
		return true;
	}

	return false;
}

int DungeonLocator::ClickLastDung()
{
	if (coords.size() <= coordIndex)
	{
		LOG("Invalid dungeon coords");
		return -1;
	}
	return MouseLeftClick(coords[coordIndex].GetAbsMidX(), coords[coordIndex].GetAbsMidY());
}
