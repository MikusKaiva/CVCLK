#pragma once

#include "Coords.h"

public class NoCompanion
{
public:
	static int DetermineLocation();
	static bool IsSlider();
	static int ClickNoCompanion();

private:
	static Coords coordsSearchArea;
	static Coords coordsBtnNoCompanion;
};