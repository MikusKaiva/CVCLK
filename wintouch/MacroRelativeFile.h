#pragma once

#include <string>

#include "FileReader.h"

class MacroRelative
{
public:
	static int StoreData(const std::string& name, const FileReader::unionValue& value);
	static int LoadFile();

	static std::string lookFor;
	static int X1, X2, Y1, Y2;
};
