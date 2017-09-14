#include "MacroStepsFile.h"

#include "UniversalFunctions.h"
#include "Log.h"

std::string MacroStepsF::lastStepName = "unknown";

int MacroStepsF::StoreData(const std::string& name, const FileReader::unionValue& value)
{
	if (name == "STEP")
	{
		if (UniversalFunctions::stepFuncParamDB.find(value.sValue) != UniversalFunctions::stepFuncParamDB.end())
		{
			LOG("Duplicate step name!");
			return -1;
		}
		UniversalFunctions::stepFuncParameters stepParams;
		InitDefaultValues(stepParams);
		UniversalFunctions::stepFuncParamDB[value.sValue] = stepParams;
		lastStepName = value.sValue;
		return 0;
	}
	else if (UniversalFunctions::stepFuncParamDB.empty())
	{
		LOG("Step name should be defined first!");
		return -1;
	}

	if (name == "INITIAL_MAX_WAIT")
	{
		UniversalFunctions::stepFuncParamDB[lastStepName].maxWait = value.iValue;
		return 0;
	}

	UniversalFunctions::fType ftype = UniversalFunctions::f_screen;
	UniversalFunctions::stepFuncArgs stepFuncArgs = {value.iValue, value.sValue};
	if (name == "LOOK_FOR")
	{
		if (UniversalFunctions::screenFuncParamDB.find(value.sValue) == UniversalFunctions::screenFuncParamDB.end())
		{
			LOG("Screen not defined!");
			return -1;
		}
		ftype = UniversalFunctions::f_screen;
	}
	else if (name == "CLICK")
	{
		if (UniversalFunctions::clickFuncParamDB.find(value.sValue) == UniversalFunctions::clickFuncParamDB.end())
		{
			LOG("Click not defined!");
			return -1;
		}
		ftype = UniversalFunctions::f_click;
	}
	else if (name == "STORE" && value.sValue == "RET")
	{
		ftype = UniversalFunctions::f_Ret;
	}
	else if (name == "CALL")
	{
		if (UniversalFunctions::stepFuncParamDB.find(value.sValue) == UniversalFunctions::stepFuncParamDB.end())
		{
			LOG("Step not defined!");
			return -1;
		}
		ftype = UniversalFunctions::f_step;
	}
	else if (name == "DRAG")
	{
		if (UniversalFunctions::dragFuncParamDB.find(value.sValue) == UniversalFunctions::dragFuncParamDB.end())
		{
			LOG("Drag not defined!");
			return -1;
		}
		ftype = UniversalFunctions::f_drag;
	}
	else if (name == "MAX_WAIT")
	{
		ftype = UniversalFunctions::f_MaxWait;
	}
	else if (name == "RETURN" && value.sValue == "RET")
	{
		ftype = UniversalFunctions::f_Return;
	}
	else if (name == "RESET")
	{
		ftype = UniversalFunctions::f_Reset;
	}
	else if (name == "WAIT")
	{
		ftype = UniversalFunctions::f_Wait;
	}
	else if (name == "CONTINUE" && value.sValue == "NEXT")
	{
		ftype = UniversalFunctions::f_Next;
	}
	else
	{
		return -1;
	}
	UniversalFunctions::stepFuncParamDB[lastStepName].steps.push_back(std::pair<UniversalFunctions::fType, UniversalFunctions::stepFuncArgs>(ftype, stepFuncArgs));

	return 0;
}

int MacroStepsF::LoadFile()
{
	return FileReader::LoadFile("macro_steps.dat", StoreData);
}

int MacroStepsF::InitDefaultValues(UniversalFunctions::stepFuncParameters& params)
{
	params.maxWait = 0;
	params.ret = -1;
	params.succ = true;
	params.steps = std::vector<std::pair<UniversalFunctions::fType, UniversalFunctions::stepFuncArgs> >();
	return 0;
}
