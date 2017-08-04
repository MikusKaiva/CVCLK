#include "FindImage.h"

#include <opencv2/opencv.hpp>
#include <string>

#include "DesktopCapture.h"
#include "Log.h"

using namespace std;
using namespace cv;

int FindImage(Mat& imgToSearch, Mat& imgLocation, int& x1, int& y1, int& x2, int& y2)
{
	Mat result = Mat(imgLocation.rows, imgLocation.cols, CV_8UC3);

	int match_method = CV_TM_SQDIFF_NORMED;
	matchTemplate(imgLocation, imgToSearch, result, match_method);

	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	if (minVal > 0.2)
	{
		return -1; //0.024 - 0.03 is ok, 1 is fail
	}

	x1 = minLoc.x;
	x2 = x1 + imgToSearch.cols;
	y1 = minLoc.y;
	y2 = y1 + imgToSearch.rows;

	return 0;
}

int FindImageInPartOfDesktop(const std::string imgFileName, int x1, int y1, int x2, int y2)
{
	Mat templ, src;
	int res = -1;

	res = GetPartOfDesktop(src, x1, y1, x2, y2);

	if (res != 0)
		LOG("Failed to get Part Of Desktop");

	if (res == 0)
	{
		templ = imread(imgFileName, IMREAD_COLOR);
		if (templ.empty())
		{
			LOG("Image '" + imgFileName + "' not found");
			res = -1;
		}
	}

	if (res == 0)
	{
		res = FindImage(templ, src, x1, y1, x2, y2);
		if (res != 0) LOG("Image '" + imgFileName + "' not found in area");
	}

	return res;
}
