#pragma once

#include <string>

#include "FileReader.h"
#include "UniversalFunctions.h"

class MacroLoops
{
public:
	static int StoreData(const std::string& name, const FileReader::unionValue& value);
	static int LoadFile();

private:
	static int InitDefaultValues(UniversalFunctions::loopFuncParameters& params);
	static std::string lastLoopName;
};