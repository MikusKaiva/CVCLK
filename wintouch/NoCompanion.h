#pragma once

#include "Coords.h"

public class NoCompanion
{
public:
	static int DetermineLocation();
	static int ClickNoCompanion();

private:
	static bool IsSlider();
	static int ClickNoCompanionBtn();

	static Coords coordsSearchArea;
	static Coords coordsBtnNoCompanion;
};