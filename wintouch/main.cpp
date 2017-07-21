
#include <opencv2/opencv.hpp>
#include "FindImage.h"

using namespace cv;

int main()
{
	char* imageName = "fck.png";
	Mat image;
	image = imread(imageName, IMREAD_COLOR);

	int x1, x2, y1, y2;
	Mat imgToSearch, imgLocation;
	imgToSearch = imread("t.png", IMREAD_COLOR);
	imgLocation = imread("fck.png", IMREAD_COLOR);
	FindImage(imgToSearch, imgLocation, x1, y1, x2, y2);
	
	rectangle(imgLocation, Rect(x1, y1, imgToSearch.cols, imgToSearch.rows), Scalar(0, 255, 0), 4);

	namedWindow(imageName, WINDOW_AUTOSIZE);
	imshow(imageName, imgLocation);
	waitKey(0);
	return 0;
}
