#include "MacroLoopsFile.h"

#include "Log.h"

std::string MacroLoops::lastLoopName = "unknown";

int MacroLoops::StoreData(const std::string& name, const FileReader::unionValue& value)
{
	if (name == "LOOP")
	{
		if (UniversalFunctions::loopFuncParamDB.find(value.sValue) != UniversalFunctions::loopFuncParamDB.end())
		{
			LOG("Duplicate step name!");
			return -1;
		}
		UniversalFunctions::loopFuncParameters loopParams;
		InitDefaultValues(loopParams);
		UniversalFunctions::loopFuncParamDB[value.sValue] = loopParams;
		lastLoopName = value.sValue;
		return 0;
	}
	else if (UniversalFunctions::loopFuncParamDB.empty())
	{
		LOG("Loop name should be defined first!");
		return -1;
	}

	if (name == "MAX_FAILURES")
	{
		UniversalFunctions::loopFuncParamDB[lastLoopName].maxFailures = value.iValue;
	}
	else if (name == "STEP")
	{
		if (UniversalFunctions::stepFuncParamDB.find(value.sValue) == UniversalFunctions::stepFuncParamDB.end())
		{
			LOG("Step not defined!");
			return -1;
		}
		UniversalFunctions::loopFuncParamDB[lastLoopName].steps.push_back(std::pair<std::string, std::string>(value.sValue, ""));
	}
	else if (name == "STEP_2")
	{
		if (UniversalFunctions::stepFuncParamDB.find(value.sValue) == UniversalFunctions::stepFuncParamDB.end())
		{
			LOG("Step not defined!");
			return -1;
		}
		int size = UniversalFunctions::loopFuncParamDB[lastLoopName].steps.size();
		if (size == 0)
		{
			LOG("at least one STEP should be before STEP_2");
			return -1;
		}
		if (!UniversalFunctions::loopFuncParamDB[lastLoopName].steps[size - 1].second.empty())
		{
			LOG("STEP_2 is defined already");
			return -1;
		}
		UniversalFunctions::loopFuncParamDB[lastLoopName].steps[size - 1].second = value.sValue;
	}
	else
	{
		return -1;
	}

	return 0;
}

int MacroLoops::LoadFile()
{
	return FileReader::LoadFile("macro_loops.dat", StoreData);
}

int MacroLoops::InitDefaultValues(UniversalFunctions::loopFuncParameters& params)
{
	params.maxFailures = 1000;
	params.steps = std::vector<std::pair<std::string, std::string> >();
	return 0;
}