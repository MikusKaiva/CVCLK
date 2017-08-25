#include "MacroFunctions.h"

#include <Windows.h>

#include "MacroFile.h"
#include "Log.h"
#include "DungeonLocator.h"
#include "constants.h"
#include "Energy.h"
#include "ConnectionError.h"
#include "DailyQuestCompleted.h"
#include "Nox.h"
#include "Missions.h"
#include "NoCompanion.h"
#include "Depart.h"
#include "Attack.h"
#include "ResultsGil.h"
#include "ResultsExp.h"
#include "ResultsItems.h"

#define STOP_THREAD -2
#define PROCESS_PAUSE_AND_STOP if (ProcessPauseAndStop() == STOP_THREAD) return STOP_THREAD

int MacroFunctions::isPaused = false;
int MacroFunctions::isStopped = false;

int MacroFunctions::Run(std::string dungName)
{
	int ret = -1;

	if (IsNoxPresent() < 0)
	{
		LOG("Nox Not Found ");
		return -1;
	}

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

int MacroFunctions::MacroFuncCaller(macroFuncType function)
{
	PROCESS_PAUSE_AND_STOP;
	
	return function();
}

int MacroFunctions::IsNoxPresent()
{
	return Nox::DetermineLocation();
}

int MacroFunctions::Wait(int miliSeconds)
{
	int step = 100;
	do
	{
		if (isStopped)
			return STOP_THREAD;
		while (isPaused)
		{
			Sleep(250);
			miliSeconds -= 250;
			if (isStopped)
				return STOP_THREAD;
		}
		Sleep(step);
		miliSeconds -= step;
	} while (miliSeconds > 0);
	return 0;
}

int MacroFunctions::ClickEarthShrine_Exit()
{
	bool notEnoughEne = false;
	int ret = -1;

	if (DungeonLocator::IsDung(E_SHRINE_EXIT))
	{
		if (DungeonLocator::ClickLastDung() == 0)
		{
			ret = Wait(1000);
			if (ret == 0 && Energy::IsMsgNoEne())
			{
				notEnoughEne = true;
			}
			
		}
	}

	if (notEnoughEne)
	{
		ret = Wait(300 * 1000);
		if (ret == 0)
		{
			ret = Energy::ClickBtnBack();
		}
		if (ret == 0)
		{
			ret = Wait(1000);
			if (ret == 0)
				ret = ClickEarthShrine_Exit();
		}
	}

	return ret;
}

int MacroFunctions::ClickConnectionError()
{
	if (ConnectionError::IsMsg())
	{
		if (ConnectionError::ClickBtnOk() == 0)
		{
			return Wait(3000);
		}
	}
	return -1;
}

int MacroFunctions::ClickDailyQuestCompletedStep()
{
	if (DailyQuestCompleted::IsMsg())
	{
		if (DailyQuestCompleted::ClickBtnClose() == 0)
		{
			return Wait(1000);
		}
	}
	return -1;
}

int MacroFunctions::ClickMissions()
{
	if (Missions::IsMsg())
	{
		if (Missions::ClickBtnNext() == 0)
		{
			return Wait(1000);
		}
	}
	return -1;
}

int MacroFunctions::ClickNoCompanion()
{
	int ret = -1;
	if (NoCompanion::IsSlider())
	{
		ret = Wait(500);
		if (ret == 0)
		{
			ret = NoCompanion::ClickNoCompanion();
		}
		if ( ret == 0)
		{
			return Wait(1000);
		}
	}
	return ret;
}

int MacroFunctions::ClickDepart()
{
	if (Depart::IsMsg())
	{
		if (Depart::ClickBtnDepart() == 0)
		{
			return Wait(3000);
		}
	}
	return -1;
}

int MacroFunctions::WaitAttack()
{
	int ret = -1;
	int howLong = 15;

	while (howLong >= 0)
	{
		if (Attack::IsMsg()) 
		{
			ret = 0;
			break;
		}
		ret = ClickConnectionError();
		if (ret == 0)
		{
			howLong = 10;
			continue;
		}
		if (ret == STOP_THREAD)
		{
			break;
		}
		howLong--;
		ret = Wait(1000);
		if (ret != 0)
		{
			break;
		}
		ret = -1;
	}
	return ret;
}

int MacroFunctions::ClickAttack()
{
	int ret = -1;
	bool clickChars = true;

	do
	{
		if (Attack::IsRepeatDisabled())
		{
			ret = Wait(200);
		}
		else if (Attack::IsRepeat())
		{
			ret = Attack::ClickBtnRepeat();
			if (clickChars && ret == 0)
			{
				Sleep(200);
				ret = Attack::ClickChars();
				clickChars = false;
			}
			if (ret == 0)
				ret = Wait(1000);
		}
		else 
		{
			break;
		}
	} while (ret == 0);

	return ret;
}

int MacroFunctions::WaitResults()
{
	int ret = -1;
	int howLong = 15;

	while (howLong >= 0)
	{
		if (ResultsGil::IsMsg())
		{
			ret = 0;
			break;
		}
		ret = ClickConnectionError();
		if (ret == 0)
		{
			howLong = 10;
			continue;
		}
		if (ret == STOP_THREAD)
		{
			break;
		}
		howLong--;
		ret = Wait(1000);
		if (ret != 0)
		{
			break;
		}
		ret = -1;
	}
	return ret;
}

int MacroFunctions::ClickResultsGil()
{
	int ret = -1;
	if (ResultsGil::IsMsg())
	{
		int i = 0;
		do
		{
			ret = ResultsGil::ClickResultsGil();
			if (ret == 0) ret = Wait(500);
		} while (ret == 0 && ++i <= 3);

		if (ret == 0)
		{
			ResultsGil::ClickNextBtn();
		}

		if (ret == 0)
		{
			ret = Wait(1000);
		}
	}
	return ret;
}

int MacroFunctions::ClickResultsExp()
{
	int ret = -1;
	if (ResultsExp::IsMsg())
	{
		if (ResultsExp::ClickResultsExp() == 0)
		{
			return Wait(1000);
		}
	}
	return -1;
}

int MacroFunctions::ClickResultsItems()
{
	int ret = -1;
	if (ResultsItems::IsMsg())
	{
		ret = ResultsItems::ClickResultsItems();

		if (ret == 0)
		{
			ret = Wait(2000);
		}

		if (ret == 0)
		{
			ResultsItems::ClickNextBtn();
		}

		if (ret == 0)
		{
			ret = Wait(3000);
		}
	}
	return ret;
}
