#include "SearchObj.h"
#include <opencv2/opencv.hpp>

#include "FindImage.h"
#include "DesktopCapture.h"
#include "MouseControl.h"

using namespace cv;
using namespace std;

SearchObj::SearchObj(string imgName, int searchAreaMidY, int searchAreaHeight)
	: searchAreaMidY(searchAreaMidY)
	, searchAreaHeight(searchAreaHeight)
	, x(0)
	, y(0)
	, found(false)
{
	imgToSearch = imread(imgName, IMREAD_COLOR);
	searchAreaMidX = (noxX2 - noxX1) / 2;
	searchAreaWidth = imgToSearch.cols * 3;
}

SearchObj::~SearchObj()
{
}

void SearchObj::Init(std::string imgName, int searchAreaMidY, int searchAreaHeight, int searchAreaMidX, int searchAreaWidth)
{
	this->searchAreaMidY = searchAreaMidY;
	this->searchAreaHeight = searchAreaHeight;
	this->x = 0;
	this->y = 0;
	this->found = false;
	{
		imgToSearch = imread(imgName, IMREAD_COLOR);
		if (searchAreaMidX == -1)
			this->searchAreaMidX = (noxX2 - noxX1) / 2;
		else
			this->searchAreaMidX = searchAreaMidX;
		if (searchAreaWidth == -1)
			this->searchAreaWidth = imgToSearch.cols * 3;
		else
			this->searchAreaWidth = searchAreaWidth;
	}
}

int SearchObj::Search(bool isNox)
{
	if (imgToSearch.empty()) return -1;
	found = false;
	Mat imgPartOfScreen;
	int x1 = noxX1 + searchAreaMidX - searchAreaWidth / 2;
	if (x1 < 0) x1 = 0;
	int y1 = noxY + searchAreaMidY - searchAreaHeight / 2;
	if (y1 < 0) y1 = 0;
	int x2 = x1 + searchAreaWidth;
	int y2 = y1 + searchAreaHeight;
	int res = GetPartOfDesktop(imgPartOfScreen, x1, y1, x2, y2);

	//if (!isNox) 
	//{
	//	namedWindow("test", WINDOW_AUTOSIZE);
	//	imshow("test", imgPartOfScreen);
	//	waitKey(0);
	//}

	if (res < 0) return res;
	x = x1;
	y = y1;
	res = FindImage(imgToSearch, imgPartOfScreen, x1, y1, x2, y2);
	if (res < 0) return res;
	x += (x2 + x1) / 2;
	y += (y2 + y1) / 2;
	found = true;

	if (isNox)
	{
		noxX1 = x1;
		noxX2 = x2;
		noxY = y2;
		noxWidth = x2 - x1;
	}

	return res;
}

int SearchObj::Action()
{
	if (found)
		return MouseLeftClick(x, y);
	return -1;
}

int SearchObj::noxX1 = 0;
int SearchObj::noxX2 = 600;
int SearchObj::noxY = 0;
int SearchObj::noxWidth = 600;


SearchSlider::SearchSlider(string imgName, int searchAreaMidY, int searchAreaHeight)
	: SearchObj(imgName, searchAreaMidY, searchAreaHeight)
{ }

int SearchSlider::Action()
{
	if (found)
	{
		int res = SetMousePosition(x, y);
		if (res < 0) return -1;
		res = MouseLeftDown();
		if (res < 0) return -1;
		res = MoveMouseTo(x, y + 600, 500);
		if (res < 0) return -1;
		res = MouseLeftUp();
		return res;
	}
	return -1;
}
