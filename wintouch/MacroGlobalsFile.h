#pragma once

#include "FileReader.h"

class MacroGlobals
{
public:
	static int StoreData(const std::string& name, const FileReader::unionValue& value);
	static int LoadFile();

	// below is formula used to calculate default search area's X1 coord
	// X1 = X1_REF_POINT + HORIZONTAL_UNITS * X1_KOEF / 1000
	static int X1_REF_POINT, HORIZONTAL_UNITS, X1_KOEF;

	// formula for X2 coord depends on choice.By default we search in the middle
	// of app OR we can search relatively to X1 coord
	// IF HORIZ_MIDDLE = 1 (default), X2 = X1_REF_POINT - X1 + X2_REF_POINT
	// ELSE X2 = X1 + HORIZONTAL_UNITS * X2_KOEF / 1000
	static int X2_REF_POINT, X2_KOEF;

	// Y1 = Y1_REF_POINT + VERTICAL_UNITS * Y1_KOEF / 1000
	// Y2 = Y1 + VERTICAL_UNITS * Y2_KOEF / 1000
	static int Y1_REF_POINT, VERTICAL_UNITS, Y1_KOEF, Y2_KOEF;

	// default wait time before / after click
	static int AFTER_CLICK_TIME, BEFORE_CLICK_TIME;

	// mouse drag and drop distance will be #_UNITS * #_DRAG_KOEF / 1000
	static int X_DRAG_KOEF, Y_DRAG_KOEF;
};
