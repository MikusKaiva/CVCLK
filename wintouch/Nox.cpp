#include "Nox.h"
#include <opencv2/opencv.hpp>
#include "DesktopCapture.h"
#include "FindImage.h"
#include "FFapp.h"

using namespace cv;

int Nox::Start() { return 0; }
int Nox::StartApp(std::string appName) { return 0; }
bool Nox::IsRunning() { return true; }
int Nox::DetermineLocation() 
{
	const int WIDTH = 591;
	const int HEIGHT = 1017;
	const int SEARCH_AREA_X2 = 1920;
	const int SEARCH_AREA_Y2 = 70;

	Mat templ, src;
	int res = -1;
	int x1, y1, x2, y2;

	res = GetPartOfDesktop(src, 0, 0, SEARCH_AREA_X2, SEARCH_AREA_Y2);
	if (res == 0)
	{
		templ = imread("images/nox.png", IMREAD_COLOR);
		if (templ.empty())
		{
			res = -1;
		}
	}

	if (res == 0)
	{
		res = FindImage(templ, src, x1, y1, x2, y2);
	}

	if (res == 0 && (x1 != coords.GetAbsX1() || x2 != coords.GetAbsX2() || y1 != coords.GetAbsY1() || y2 != coords.GetAbsY2()))
	{
		coords.SetOffset(x1, y1);
		coords.SetAbsX(x1, x1 + WIDTH);
		coords.SetAbsY(y1, y1 + HEIGHT);
		FFapp::DetermineLocation();
	}

	return res;
}

Coords Nox::coords = Coords(0, 0, 360, 640, 0, 0);
const int Nox::TOP_BAR_HEIGHT = 35;
const int Nox::RIGHT_BAR_WIDTH = 38;