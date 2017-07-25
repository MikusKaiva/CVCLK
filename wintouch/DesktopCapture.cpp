#include <Windows.h>
#include <opencv2/imgproc.hpp>
#include "DesktopCapture.h"

using namespace cv;

int GetAllDesktop(Mat& src)
{
	HWND hwnd = GetDesktopWindow();
	RECT dimensions;
	GetClientRect(hwnd, &dimensions);
	return GetPartOfDesktop(src, dimensions.left, dimensions.top, dimensions.right, dimensions.bottom);
}

int GetPartOfDesktop(cv::Mat& src, int x1, int y1, int x2, int y2)
{
	if (x1 > x2) swap(x1, x2);
	if (y1 > y2) swap(y1, y2);
	int w = abs(x2 - x1);
	int h = abs(y2 - y1);
	if (w == 0 || h == 0) return -1;

	HDC hdcSource = GetDC(NULL);
    HDC hdcMemory = CreateCompatibleDC(hdcSource);

	// create a bitmap
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcSource, w, h);
	// use the previously created device context with the bitmap
	SelectObject(hdcMemory, hBitmap);
	// copy from the window device context to the bitmap device context
	cv::Mat bmpMat = Mat(h, w, CV_8UC4);
	BitBlt(hdcMemory, 0, 0, w, h, hdcSource, x1, y1, SRCCOPY);

	BITMAPINFOHEADER  bi = {0};
	bi.biSize = sizeof(bi);
	bi.biWidth = w;
	bi.biHeight = -h;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	GetDIBits(hdcMemory, hBitmap, 0, h, bmpMat.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hdcMemory to hBitmap
	cvtColor(bmpMat, src, COLOR_BGRA2BGR);

	DeleteObject(hBitmap);
	DeleteDC(hdcSource);
    DeleteDC(hdcMemory);

	return 0;
}