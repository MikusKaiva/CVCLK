#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>     // cv::Canny()
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	 char* imageName = argv[1];
	 Mat image;
	 image = imread( imageName, IMREAD_COLOR );
	 if( argc != 2 || !image.data )
	 {
	   printf( " No image data \n " );
	   return -1;
	 }
	 Mat gray_image;
	 cvtColor( image, gray_image, COLOR_BGR2GRAY );
	 imwrite( "../../images/Gray_Image.jpg", gray_image );
	 namedWindow( imageName, WINDOW_AUTOSIZE );
	 namedWindow( "Gray image", WINDOW_AUTOSIZE );
	 imshow( imageName, image );
	 imshow( "Gray image", gray_image );
	 waitKey(0);
	 return 0;
}

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