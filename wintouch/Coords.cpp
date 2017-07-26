#include "Coords.h"

Coords::Coords(int x1, int y1, int x2, int y2, int offsetX, int offsetY)
{
	SetX(x1, x2); SetY(y1, y2);
	SetOffsetX(offsetX);
	SetOffsetY(offsetY);
}
int Coords::GetX1() { return x1; }
int Coords::GetX2() { return x2; }
int Coords::GetY1() { return y1; }
int Coords::GetY2() { return y2; }

int Coords::GetAbsX1() { return GetX1() + offsetX; }
int Coords::GetAbsX2() { return GetX2() + offsetX; }
int Coords::GetAbsY1() { return GetY1() + offsetY; }
int Coords::GetAbsY2() { return GetY2() + offsetY; }

int Coords::SetX(int x1, int x2)
{
	if (x1 < x2)
	{
		this->x1 = x1;
		this->x2 = x2;
	}
	else
	{
		this->x1 = x2;
		this->x2 = x1;
	}
	return 0;
}
int Coords::SetY(int y1, int y2)
{
	if (y1 < y2)
	{
		this->y1 = y1;
		this->y2 = y2;
	}
	else
	{
		this->y1 = y2;
		this->y2 = y1;
	}
	return 0;
}
int Coords::SetAbsX(int x1, int x2) { return SetX(x1 - offsetX, x2 - offsetX); }
int Coords::SetAbsY(int y1, int y2) { return SetY(y1 - offsetY, y2 - offsetY); }
int Coords::SetOffsetX(int value) { this->offsetX = value; return 0; };
int Coords::SetOffsetY(int value) { this->offsetY = value; return 0; };

int Coords::GetMidX() { return (x1 + x2) / 2; }
int Coords::GetMidY() { return (y1 + y2) / 2; }