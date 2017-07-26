#pragma once

#include "Coords.h"

public class FFapp
{
public:
	bool IsTitleScreen();
	bool IsHomeScreen() ;
	bool IsWorldMap();
	int EnterHomeScreen();
	int EnterWorldMap();
	static int DetermineLocation();
	static Coords coords;

private:
	bool CanGoBack();
};
