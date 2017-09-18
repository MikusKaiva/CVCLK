#pragma once

#include "FileReader.h"
#include "UniversalFunctions.h"

class MacroStepsF
{
public:
	static int StoreData(const std::string& name, const FileReader::unionValue& value);
	static int LoadFile();

private:
	static int InitDefaultValues(UniversalFunctions::stepFuncParameters& params);
	static std::string lastStepName;
};
