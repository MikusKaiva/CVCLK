#include "MacroFunctions.h"

#include <Windows.h>

#include "MacroFile.h"
#include "Log.h"

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
		for (MacroStep uniqueStep : uniqueSteps)
		{
			Sleep(100);
			if (uniqueStep.function() == 0)
			{
				failures = 0;
				if (uniqueStep.nextStepName >= 0)
					RunSequential(MacroFile::macroStepDB[dungIndex].sequentialSteps, uniqueStep.nextStepName);
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
			break;
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
		while (sequentalStep != sequentialSteps.end() && sequentalStep->function() == 0)
		{
			Sleep(100);
			++sequentalStep;
			//if (sequentalStep == sequentialSteps.end()) sequentalStep = sequentialSteps.begin();
		}
	}

	return ret;
}
int MacroFunctions::IsNoxPresent()
{
	LOG("IsNoxPresent");
	return 0;
}
