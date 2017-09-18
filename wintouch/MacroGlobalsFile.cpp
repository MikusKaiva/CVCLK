#include "MacroGlobalsFile.h"

int MacroGlobals::X1_REF_POINT = 0;
int MacroGlobals::HORIZONTAL_UNITS = 500;
int MacroGlobals::X1_KOEF = 0;
int MacroGlobals::X2_REF_POINT = 500;
int MacroGlobals::X2_KOEF = 1000;
int MacroGlobals::Y1_REF_POINT = 0;
int MacroGlobals::VERTICAL_UNITS = 500;
int MacroGlobals::Y1_KOEF = 0;
int MacroGlobals::Y2_KOEF = 1000;
int MacroGlobals::AFTER_CLICK_TIME = 1000;
int MacroGlobals::BEFORE_CLICK_TIME = 0;
int MacroGlobals::X_DRAG_KOEF = 0;
int MacroGlobals::Y_DRAG_KOEF = 0;

int MacroGlobals::StoreData(const std::string& name, const FileReader::unionValue& value)
{
	if (name == "X1_REF_POINT")
	{
		X1_REF_POINT = value.iValue;
	}
	else if (name == "HORIZONTAL_UNITS")
	{
		HORIZONTAL_UNITS = value.iValue;
	}
	else if (name == "X1_KOEF")
	{
		X1_KOEF = value.iValue;
	}
	else if (name == "X2_REF_POINT")
	{
		X2_REF_POINT = value.iValue;
	}
	else if (name == "X2_KOEF")
	{
		X2_KOEF = value.iValue;
	}
	else if (name == "Y1_REF_POINT")
	{
		Y1_REF_POINT = value.iValue;
	}
	else if (name == "VERTICAL_UNITS")
	{
		VERTICAL_UNITS = value.iValue;
	}
	else if (name == "Y1_KOEF")
	{
		Y1_KOEF = value.iValue;
	}
	else if (name == "Y2_KOEF")
	{
		Y2_KOEF = value.iValue;
	}
	else if (name == "AFTER_CLICK_TIME")
	{
		AFTER_CLICK_TIME = value.iValue;
	}
	else if (name == "BEFORE_CLICK_TIME")
	{
		BEFORE_CLICK_TIME = value.iValue;
	}
	else if (name == "X_DRAG_KOEF")
	{
		X_DRAG_KOEF = value.iValue;
	}
	else if (name == "Y_DRAG_KOEF")
	{
		Y_DRAG_KOEF = value.iValue;
	}
	else
	{
		return -1;
	}
	return 0;
}

int MacroGlobals::LoadFile()
{
	return FileReader::LoadFile("macro_globals.dat", StoreData);
}