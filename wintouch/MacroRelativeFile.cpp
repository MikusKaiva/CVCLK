#include "MacroRelativeFile.h"
#include "Nox.h"

std::string MacroRelative::lookFor = "";
int MacroRelative::X1 = 0;
int MacroRelative::X2 = 0;
int MacroRelative::Y1 = 0;
int MacroRelative::Y2 = 0;

int MacroRelative::StoreData(const std::string& name, const FileReader::unionValue& value)
{
	if (name == "LOOK_FOR")
	{
		lookFor = value.sValue;
	}
	else if (name == "X1") 
	{
		X1 = value.iValue;
	}
	else if (name == "X2")
	{
		X2 = value.iValue;
	}
	else if (name == "Y1")
	{
		Y1 = value.iValue;
	}
	else if (name == "Y2")
	{
		Y2 = value.iValue;
	}
	else if (name == "ENABLED")
	{
		Nox::enabled = value.iValue;
	}
	else
	{
		return -1;
	}
	return 0;
}

int MacroRelative::LoadFile()
{
	return FileReader::LoadFile("macro_relative.dat", StoreData);
}