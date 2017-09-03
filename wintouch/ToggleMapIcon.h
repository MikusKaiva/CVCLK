#pragma once

#include "Coords.h"

public class ToggleMapIcon
{
public:
	static int DetermineLocation();
	static bool IsMsg();
	static int ClickMapIcon();
	static int WaitToggleMapIcon();
	
private:                                                     
	static Coords coords;
};