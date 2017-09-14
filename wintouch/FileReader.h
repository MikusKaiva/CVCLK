#pragma once

#include <string>

class FileReader
{
public:
	struct unionValue
	{
		int iValue;
		std::string sValue;
	};

	typedef int(*storeLineDataFunc)(const std::string& name, const unionValue& value);

	static int LoadFile(const std::string fileName, storeLineDataFunc storeDataFunc);
	static int ProcessLine(std::string line, std::string& name, unionValue& value);

	static void RemoveNegativeChars(std::string& line);
	static void TrimLeft(std::string& line);
	static int ExtractValue(FileReader::unionValue& value, std::string line);
	static int ExtractName(std::string& name, std::string line);
	static int ExtractDigits(std::string & dest, std::string line);
	static int ExtractString(std::string & dest, std::string line);
};