#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "DesktopCapture.h"
#include "MouseControl.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{


	 char* imageName = argv[1];
	 Mat image;
	 //GetAllDesktop(image);
	 //GetPartOfDesktop(image, 0, 0, 300, 300);
	 if( argc != 2 || !image.data )
	 {
	   printf( " No image data \n " );
	   return -1;
	 }
	 namedWindow( imageName, WINDOW_AUTOSIZE );
	 imshow( imageName, image );

	 

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


//#include <iostream>
//#include <string>
//using namespace std;
//using namespace cv;

