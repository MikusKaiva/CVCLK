#include "MacroConstantFile.h"

std::map<std::string, FileReader::unionValue>MacroConstants::constantDB = std::map<std::string, FileReader::unionValue>();

bool MacroConstants::HasConstant(std::string name)
{
	if (constantDB.count(name) > 0)
		return true;
	return false;
}

int MacroConstants::StoreData(const std::string& name, const FileReader::unionValue& value)
{
	constantDB[name] = value;
	return 0;
}

int MacroConstants::LoadFile()
{
	return FileReader::LoadFile("macro_constants.dat", StoreData);
}

