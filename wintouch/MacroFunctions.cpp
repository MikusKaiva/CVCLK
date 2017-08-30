#include "MacroFunctions.h"

#include <Windows.h>

#include "MacroFile.h"
#include "Log.h"
#include "constants.h"
#include "Wait.h"

#define PROCESS_PAUSE_AND_STOP if (ProcessPauseAndStop() == STOP_THREAD) return STOP_THREAD

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

		// add common steps, like connection error, daily quest completed
		int commonDungIndex = MacroFile::FindDung(MacroFile::ALL_DUNG_NAME);
		if (commonDungIndex >= 0)
		for (MacroStep ms : MacroFile::macroStepDB[commonDungIndex].commonSteps)
			uniqueSteps.push_back(ms);


		std::vector<MacroStep>::iterator uniqueStep = uniqueSteps.begin();
		while ( true )
		{
			ret = MacroFuncCaller(uniqueStep->function);
			if (ret == 0)
			{
				failures = 0;
				if (uniqueStep->nextStepName >= 0)
				{
					ret = RunSequential(MacroFile::macroStepDB[dungIndex].sequentialSteps, uniqueStep->nextStepName);
				}
			}
			if (ret == STOP_THREAD)
			{
				break;
			}
			else if (ret < 0)
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
		ret = MacroFuncCaller(sequentalStep->function);
		while (ret == 0)
		{
			++sequentalStep;
			if (sequentalStep == sequentialSteps.end()) sequentalStep = sequentialSteps.begin();
			ret = MacroFuncCaller(sequentalStep->function);
		}
	}

	return ret;
}

int MacroFunctions::ProcessPauseAndStop()
{
	if (WaitClass::IsStopped())
		return STOP_THREAD;
	while (WaitClass::IsPaused())
	{
		Sleep(250);
		if (WaitClass::IsStopped())
			return STOP_THREAD;
	}
	return 0;
}

int MacroFunctions::MacroFuncCaller(macroFuncType function)
{
	PROCESS_PAUSE_AND_STOP;
	
	return function();
}


