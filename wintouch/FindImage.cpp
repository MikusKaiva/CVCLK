#include "FindImage.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int FindImage(Mat& imgToSearch, Mat& imgLocation, int& x1, int& y1, int& x2, int& y2)
{
	/*static */Ptr<ORB> detector = ORB::create(1000);
	/*static */Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

	Mat imgToSearch_desc, imgLocation_desc, homography;
	vector<KeyPoint> imgToSearch_kp, imgLocation_kp;
	vector<Point2f> matched1Pts, matched2Pts;

	detector->detectAndCompute(imgToSearch, noArray(), imgToSearch_kp, imgToSearch_desc); // TODO: do not compute more than once to the same image
	detector->detectAndCompute(imgLocation, noArray(), imgLocation_kp, imgLocation_desc);

	vector< vector<DMatch> > matches;
	vector<KeyPoint> matched1, matched2;
	matcher->knnMatch(imgToSearch_desc, imgLocation_desc, matches, 2);
	for (unsigned i = 0; i < matches.size(); i++)
	{
		if (matches[i][0].distance < 0.8f * matches[i][1].distance) {
			matched1.push_back(imgToSearch_kp[matches[i][0].queryIdx]);
			matched2.push_back(imgLocation_kp[matches[i][0].trainIdx]);
		}
	}
	
	for (vector<KeyPoint>::iterator it = matched1.begin(); it != matched1.end(); ++it)
	{
		matched1Pts.push_back(Point2f(it->pt));
	}
	for (vector<KeyPoint>::iterator it = matched2.begin(); it != matched2.end(); ++it)
	{
		matched2Pts.push_back(Point2f(it->pt));
	}

	if (matched1.size() >= 4) {
		homography = estimateRigidTransform(matched1Pts, matched2Pts, true);
	}

	if (matched1.size() < 4 || homography.empty()) {
		return -1;
	}
	
	int imgToSearchHalfWidth = imgToSearch.cols/2;
	int imgToSearchHalfHeight = imgToSearch.rows/2;
	std::vector<Point2f> imgToSearchCenter(1), imgLocationCenter(1);
	imgToSearchCenter[0] = cvPoint(imgToSearchHalfWidth, imgToSearchHalfHeight);

	cv::Mat zRow = cv::Mat::zeros(1,homography.cols,homography.type());
	zRow.at<double>(0, homography.cols - 1)= 1.0;
	homography.push_back(zRow);
	perspectiveTransform(imgToSearchCenter, imgLocationCenter, homography);

	x1 = static_cast<int>(imgLocationCenter[0].x - imgToSearchHalfWidth);
	x2 = x1 + imgToSearch.rows;
	y1 = static_cast<int>(imgLocationCenter[0].y - imgToSearchHalfHeight);
	y2 = y1 + imgToSearch.cols;

	return 0;
}