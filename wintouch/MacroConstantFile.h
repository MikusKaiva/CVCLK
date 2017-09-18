#pragma once

#include <map>

#include "FileReader.h"

class MacroConstants
{
public:
	static bool HasConstant(std::string name);
	static int StoreData(const std::string& name, const FileReader::unionValue& value);
	static int LoadFile();

	static std::map<std::string, FileReader::unionValue> constantDB;
};