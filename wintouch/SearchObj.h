#pragma once
#include <opencv2/opencv.hpp>

class SearchObj
{
public:
	SearchObj::SearchObj() { };
	SearchObj(std::string imgName, int searchAreaMidY, int searchAreaHeight);
	virtual ~SearchObj();
	void Init(std::string imgName, int searchAreaMidY, int searchAreaHeight, int searchAreaMidX = -1, int searchAreaWidth = -1);
	int Search(bool isNox = false);
	virtual int Action();

	int searchAreaMidX, searchAreaMidY, searchAreaWidth, searchAreaHeight;
	int x, y;

	static int noxX1, noxX2, noxY, noxWidth, noxHeight;

protected:
	bool found;

private:
	cv::Mat imgToSearch;
};


class SearchSlider : public SearchObj
{
public:
	SearchSlider::SearchSlider() { };
	SearchSlider(std::string imgName, int searchAreaMidY, int searchAreaHeight);
	virtual int Action();
};



