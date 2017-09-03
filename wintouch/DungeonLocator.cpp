#include "DungeonLocator.h"

#include <opencv2/opencv.hpp>

#include "FFapp.h"
#include "constants.h"
#include "Log.h"
#include "FindImage.h"
#include "MouseControl.h"
#include "Energy.h"
#include "Missions.h"
#include "NoCompanion.h"
#include "Depart.h"
#include "Attack.h"
#include "ResultsGil.h"
#include "ResultsExp.h"
#include "ResultsItems.h"

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
	Energy::DetermineLocation();
	Missions::DetermineLocation();
	NoCompanion::DetermineLocation();
	Depart::DetermineLocation();
	Attack::DetermineLocation();
	ResultsGil::DetermineLocation();
	ResultsExp::DetermineLocation();
	ResultsItems::DetermineLocation();
	
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

	int x1 = coords[coordIndex].GetAbsX1(); 
	int y1 = coords[coordIndex].GetAbsY1();
	int x2 = coords[coordIndex].GetAbsX2();
	int y2 = coords[coordIndex].GetAbsY2();

	if (FindImageInPartOfDesktop(templName, x1, y1, x2, y2) == 0)
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
