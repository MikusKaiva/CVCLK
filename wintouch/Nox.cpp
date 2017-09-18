#include "Nox.h"
#include <opencv2/opencv.hpp>
#include "DesktopCapture.h"
#include "FindImage.h"
#include "Log.h"

#include "MacroRelativeFile.h"
#include "MacroGlobalsFile.h"

using namespace cv;

int Nox::DetermineLocation() 
{
	const int WIDTH = MacroGlobals::HORIZONTAL_UNITS;
	const int HEIGHT = MacroGlobals::VERTICAL_UNITS;
	const int SEARCH_AREA_X1 = MacroRelative::X1;
	const int SEARCH_AREA_Y1 = MacroRelative::Y1;
	const int SEARCH_AREA_X2 = MacroRelative::X2;
	const int SEARCH_AREA_Y2 = MacroRelative::Y2;

	if (!enabled)
	{
		coords.SetOffset(0, 0);
		coords.SetAbsX(0, WIDTH);
		coords.SetAbsY(0, HEIGHT);
		return 0;
	}

	Mat templ, src;
	int res = -1;
	int x1, y1, x2, y2;

	res = GetPartOfDesktop(src, SEARCH_AREA_X1, SEARCH_AREA_Y1, SEARCH_AREA_X2, SEARCH_AREA_Y2);
	if (res != 0) LOG("Failed to get Part Of Desktop");

	if (res == 0)
	{
		templ = imread(MacroRelative::lookFor, IMREAD_COLOR);
		if (templ.empty())
		{
			LOG("Image '" + MacroRelative::lookFor + "' not found");
			res = -1;
		}
	}

	if (res == 0)
	{
		res = FindImage(templ, src, x1, y1, x2, y2);
		if (res != 0) LOG("App not found on desktop");
	}

	if (res == 0 && (x1 != coords.GetAbsX1() || y1 != coords.GetAbsY1()))
	{
		coords.SetOffset(x1, y1);
		coords.SetAbsX(x1, x1 + WIDTH);
		coords.SetAbsY(y1, y1 + HEIGHT);
	}

	return res;
}

Coords Nox::coords = Coords(-1, -1, 360, 640);
bool Nox::enabled = true;
