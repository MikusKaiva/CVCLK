//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main( int argc, char** argv )
//{
//	 char* imageName = argv[1];
//	 Mat image;
//	 image = imread( imageName, IMREAD_COLOR );
//	 if( argc != 2 || !image.data )
//	 {
//	   printf( " No image data \n " );
//	   return -1;
//	 }
//	 Mat gray_image;
//	 cvtColor( image, gray_image, COLOR_BGR2GRAY );
//	 imwrite( "../../images/Gray_Image.jpg", gray_image );
//	 namedWindow( imageName, WINDOW_AUTOSIZE );
//	 namedWindow( "Gray image", WINDOW_AUTOSIZE );
//	 imshow( imageName, image );
//	 imshow( "Gray image", gray_image );
//	 waitKey(0);
//	 return 0;
//}

//#include "MouseControl.h"
//#include <iostream>
//
//int main()
//{
//	int x = 0;
//	int y = 0;
//	SetMousePosition(600, 600);
//	GetMousePosition(x, y);
//	std::cout << "x=" << x << ", y=" << y << std::endl;
//	MoveMouseTo(300, 300);
//	GetMousePosition(x, y);
//	std::cout << "x=" << x << ", y=" << y;
//	system("pause");
//	//LeftClick();
//	system("pause");
//}

#include <opencv2/features2d.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <iomanip>


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
		return 0;
	}

	//-- Get the corners from imgToSearch
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); 
	obj_corners[1] = cvPoint(imgToSearch.cols, 0);
	obj_corners[2] = cvPoint(imgToSearch.cols, imgToSearch.rows); 
	obj_corners[3] = cvPoint(0, imgToSearch.rows);
	std::vector<Point2f> scene_corners(4);

	cv::Mat zRow = cv::Mat::zeros(1,homography.cols,homography.type());
	zRow.at<double>(0, homography.cols - 1)= 1.0;
	homography.push_back(zRow);
	perspectiveTransform(obj_corners, scene_corners, homography);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	line(imgLocation, scene_corners[0], scene_corners[1], Scalar(0, 255, 0), 4);
	line(imgLocation, scene_corners[1], scene_corners[2], Scalar(0, 255, 0), 4);
	line(imgLocation, scene_corners[2], scene_corners[3], Scalar(0, 255, 0), 4);
	line(imgLocation, scene_corners[3], scene_corners[0], Scalar(0, 255, 0), 4);
}

int main()
{
	char* imageName = "fck.png";
	Mat image;
	image = imread(imageName, IMREAD_COLOR);

	//Rect rec = Rect(50, 20, 200, 100);
	//Scalar color = Scalar(3,150,0);
	//rectangle(image, rec, color, 5);
	int x1, x2, y1, y2;
	Mat imgToSearch, imgLocation;
	imgToSearch = imread("t.png", IMREAD_COLOR);
	imgLocation = imread("fck.png", IMREAD_COLOR);
	FindImage(imgToSearch, imgLocation, x1, y1, x2, y2);

	namedWindow(imageName, WINDOW_AUTOSIZE);
	imshow(imageName, imgLocation);
	waitKey(0);
	return 0;
}
