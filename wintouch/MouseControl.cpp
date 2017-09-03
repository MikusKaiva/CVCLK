#include "MouseControl.h"
#include <windows.h>

//
// Desc    : Clicks the left mouse button down and releases it.
// Returns : 0
//
int MouseLeftClick()
{  
	int res = MouseLeftDown();
	if (res == 0)
		res = MouseLeftUp();
	return res;
}

int MouseLeftClick(const int x, const int y)
{
	int prevX, prevY;
	int res = GetMousePosition(prevX, prevY);
	if (res == 0)
		res = SetMousePosition(x, y);
	if (res == 0)
		res = MouseLeftClick();
	if (res == 0)
		SetMousePosition(prevX, prevY);
	return res;
}

//
// Desc    : Clicks the left mouse button down
// Returns : 0
//
int MouseLeftDown()
{
	INPUT    Input={0};													// Create our input.
	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

	return 0;
}

//
// Desc    : Releases the left mouse button
// Returns : 0
//
int MouseLeftUp()
{
	INPUT    Input={0};													// Create our input.
	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

	return 0;
}

//
// Desc    : Gets the cursors current position on the screen.
// Returns : The mouses current on screen position.
// Info    : Used a static POINT, as sometimes it would return trash values
//
int GetMousePosition(int &x, int &y)
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	x = mouse.x;
	y = mouse.y;
	return 0;
}

//
// Desc    : Sets the cursors position to the point you enter (POINT& mp).
// Returns : 0.
//
int SetMousePosition(const int x, const int y)
{
	if (x < 0 || y < 0)
		return -1;

	long fScreenWidth	    = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	long fScreenHeight	    = GetSystemMetrics( SM_CYSCREEN ) - 1; 

	if (static_cast<long>(x) > fScreenWidth || static_cast<long>(y) > fScreenHeight)
		return -1;

	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx		        = x * ( 65535.0f / fScreenWidth  );
	float fy		        = y * ( 65535.0f / fScreenHeight );		  
				
	INPUT Input             = { 0 };			
	Input.type		        = INPUT_MOUSE;

	Input.mi.dwFlags	    = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
				
	Input.mi.dx		        = (long)fx;
	Input.mi.dy		        = (long)fy;

	SendInput(1,&Input,sizeof(INPUT));
	return 0;
}

int MoveMouseTo(const int x, const int y, const int timeMiliseconds)
{
	int steps = timeMiliseconds / 5;
	if (steps == 0)
		return SetMousePosition(x, y);

	int startX = 0;
	int startY = 0;
	int res = 0;
	GetMousePosition(startX, startY);
	
	double stepSizeX = static_cast<double>(x - startX) / steps;
	double stepSizeY = static_cast<double>(y - startY) / steps;

	for (int i = 0; i <= steps && res == 0; ++i)
	{
		res = SetMousePosition(startX + stepSizeX * i, startY + stepSizeY * i);
		Sleep(5);
	}
	return res;
}