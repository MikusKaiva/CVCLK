#pragma once

public class Coords
{
public:
	Coords(int x1, int y1, int x2, int y2, int offsetX, int offsetY);
	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();

	int GetAbsX1();
	int GetAbsX2();
	int GetAbsY1();
	int GetAbsY2();

	int SetX(int x1, int x2);
	int SetY(int y1, int y2);
	int SetAbsX(int x1, int x2);
	int SetAbsY(int y1, int y2);
	int SetOffsetX(int value);
	int SetOffsetY(int value);

	int GetMidX();
	int GetMidY();

private:
	int x1, x2, y1, y2, offsetX, offsetY;
};