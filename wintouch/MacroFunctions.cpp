#include "MacroFunctions.h"

#include <Windows.h>

#include "MacroFile.h"
#include "Log.h"

#define STOP_THREAD -2
#define PROCESS_PAUSE_AND_STOP if (ProcessPauseAndStop() == STOP_THREAD) return STOP_THREAD

int MacroFunctions::isPaused = false;
int MacroFunctions::isStopped = false;

int MacroFunctions::Run(std::string dungName)
{
	int ret = -1;
	int dungIndex = MacroFile::FindDung(dungName);
	int maxFailures = 100;
	int failures = 0;
	if (dungIndex < 0)
	{
		LOG("Dung not found, name: " + dungName);
	}
	if (dungIndex >= 0)
	{
		std::vector<MacroStep> uniqueSteps = MacroFile::macroStepDB[dungIndex].uniqueSteps;
		std::vector<MacroStep>::iterator uniqueStep = uniqueSteps.begin();
		while ( true )
		{
			Sleep(100);
			ret = MacroFuncCaller(uniqueStep->function);
			if (ret == 0)
			{
				failures = 0;
				if (uniqueStep->nextStepName >= 0)
					RunSequential(MacroFile::macroStepDB[dungIndex].sequentialSteps, uniqueStep->nextStepName);
			}
			else if (ret == STOP_THREAD)
			{
				break;
			}
			else
			{
				++failures;
			}
			if (failures >= maxFailures)
			{
				LOG("Max Failure count reached, stopping.. " + dungName);
				break;
			}
			++uniqueStep;
			if (uniqueStep == uniqueSteps.end()) uniqueStep = uniqueSteps.begin();
		}
	}
	return ret;
}
int MacroFunctions::RunSequential(std::vector<MacroStep>& sequentialSteps, int stepName)
{
	int stepIndex = MacroFile::FindStep(sequentialSteps, stepName);
	int ret = 0;
	if (stepIndex < 0)
	{
		LOG("Step not found");
		ret = -1;
	}
	if (sequentialSteps.empty())
	{
		LOG("No macros in sequentialSteps");
		ret = -1;
	}

	if (ret == 0)
	{
		std::vector<MacroStep>::iterator sequentalStep = sequentialSteps.begin();
		while (MacroFuncCaller(sequentalStep->function) == 0)
		{
			Sleep(100);
			++sequentalStep;
			if (sequentalStep == sequentialSteps.end()) sequentalStep = sequentialSteps.begin();
		}
	}

	return ret;
}


int MacroFunctions::MacroFuncCaller(macroFuncType function)
{
	PROCESS_PAUSE_AND_STOP;

	function();
	return 0;
}

int MacroFunctions::IsNoxPresent()
{
	LOG("IsNoxPresent");
	return 0;
}

int MacroFunctions::ProcessPauseAndStop()
{
	if (isStopped)
		return STOP_THREAD;
	while (isPaused)
	{
		Sleep(250);
		if (isStopped)
			return STOP_THREAD;
	}
	return 0;
}
