#pragma once

public class Coords
{
public:
	Coords(int x1, int y1, int x2, int y2);
	int GetX1();
	int GetX2();
	int GetY1();
	int GetY2();

	int GetAbsX1();
	int GetAbsX2();
	int GetAbsY1();
	int GetAbsY2();
	int GetOffsetX();
	int GetOffsetY();

	int SetX	(int x1, int x2);
	int SetY	(int y1, int y2);
	int SetAbsX	(int x1, int x2);
	int SetAbsY	(int y1, int y2);
	int SetOffset(int offsetX, int offsetY);

	int GetMidX();
	int GetMidY();
	int GetAbsMidX();
	int GetAbsMidY();

	int GetWidth();
	int GetHeight();

private:
	int x1, x2, y1, y2;
	static int offsetX, offsetY;
};