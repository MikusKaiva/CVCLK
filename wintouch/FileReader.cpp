#include "FileReader.h"

#include <fstream>
#include <algorithm>

#include "Log.h"
#include "MacroConstantFile.h"

using namespace std;

int FileReader::LoadFile(const std::string fileName, storeLineDataFunc storeDataFunc)
{
	LOG("Reading file: " + fileName);
	ifstream f(fileName);
	int ret = -1;

	if (f.is_open())
	{
		string line;
		std::string name;
		FileReader::unionValue value;

		while (getline(f, line))
		{
			ret = FileReader::ProcessLine(line, name, value);
			if (ret < 0)
			{
				LOG("invalid line: " + line);
				break;
			}
			if (!name.empty())
			{
				ret = storeDataFunc(name, value);
			}
			if (ret < 0)
			{
				LOG("Error when storing data, line: " + line);
				break;
			}
		}

		f.close();
	}
	else
	{
		LOG("Can't open " + fileName);
	}

	return ret;
}

int FileReader::ProcessLine(std::string line, std::string& name, unionValue& value)
{
	name = "";
	FileReader::RemoveNegativeChars(line);
	FileReader::TrimLeft(line);
	if (line.empty() || line[0] == '#') 
		return 0;

	FileReader::ExtractName(name, line);
	if (name.empty()) 
		return -1;

	line = line.substr(name.length());
	FileReader::TrimLeft(line);

	if (ExtractValue(value, line) < 0) 
		return -1;

	return 0;
}

int FileReader::ExtractValue(FileReader::unionValue& value, std::string line)
{
	value.iValue = -1;
	value.sValue = "";

	if (line.empty()) return -1;

	char ch = line[0];
	string dest;

	if (isdigit(ch))
	{
		FileReader::ExtractDigits(dest, line);
		value.iValue = atoi(dest.c_str());
		return 0;
	}
	else if (ch == '"')
	{
		if (FileReader::ExtractString(dest, line) == 0)
		{
			value.sValue = dest;
			return 0;
		}
	}
	else
	{
		FileReader::ExtractName(dest, line);
		if (dest.empty())
			return -1;
		if (MacroConstants::HasConstant(dest))
		{
			value = MacroConstants::constantDB[dest];
			return 0;
		}
	}

	return -1;
}

void FileReader::RemoveNegativeChars(std::string& line)
{
	int i = 0;
	for (char c : line)
	{
		if (c >= 0) break;
		i++;
	}
	if (i > 0) line = line.substr(i);
}

void FileReader::TrimLeft(std::string& line)
{
	int i = 0;
	for (char c : line)
	{
		if (!isspace(c)) break;
		i++;
	}
	if (i > 0) line = line.substr(i);
}

int FileReader::ExtractName(std::string& name, std::string line)
{
	name = "";
	if (line.empty()) return -1;

	char ch = line[0];
	if (!( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' )) return -1;

	for (char c : line)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || isdigit(c))
			name += c;
		else if (isspace(c))
			return 0;
		else
		{
			return -1;
		}
	}
	return 0;
}

int FileReader::ExtractDigits(std::string& dest, std::string line)
{
	dest = "";
	if (line.empty()) return -1;

	char ch = line[0];
	if (!isdigit(ch)) return -1;

	for (char c : line)
	{
		if (isdigit(c))
			dest += c;
		else if (isspace(c))
			return 0;
		else
		{
			return -1;
		}
	}
	return 0;
}

int FileReader::ExtractString(std::string& dest, std::string line)
{
	dest = "";
	if (line.empty()) return -1;

	char ch = line[0];
	if (ch != '"') return -1;

	line = line.substr(1);

	for (char c : line)
	{
		if (c != '"')
			dest += c;
		else
		{
			return 0;
		};
	}
	return -1;
}