#include "MacroFunctions.h"

#include <Windows.h>
#include "SearchObj.h"


MacroFunctions::MacroFunctions()
{
	earthShrineSteps.push_back(FunctionName(ClickDungeon				, &MacroFunctions::ClickEarthShrine_Exit	));
	earthShrineSteps.push_back(FunctionName(ClickNextStep				, &MacroFunctions::CLickNext				));
	earthShrineSteps.push_back(FunctionName(ClickRepeatStep				, &MacroFunctions::ClickRepeat				));
	earthShrineSteps.push_back(FunctionName(ClickNoCompanionStep		, &MacroFunctions::ClickNoCompanion			));
	earthShrineSteps.push_back(FunctionName(ClickDepartStep				, &MacroFunctions::ClickDepart				));
	earthShrineSteps.push_back(FunctionName(ClickAttackStep				, &MacroFunctions::ClickAttack				));
	earthShrineSteps.push_back(FunctionName(ClickResultsGilStep			, &MacroFunctions::ClickResultsGil			));
	earthShrineSteps.push_back(FunctionName(ClickResultsExpStep			, &MacroFunctions::ClicResultsExp			));
	earthShrineSteps.push_back(FunctionName(ClickResultsItemsStep		, &MacroFunctions::ClicResultsItems			));
	earthShrineSteps.push_back(FunctionName(ClickConnectionErrorStep	, &MacroFunctions::ClickConnectionError		));
	earthShrineSteps.push_back(FunctionName(ClickDailyQuestCompletedStep, &MacroFunctions::ClickDailyQuestCompleted	));
}

MacroFunctions::~MacroFunctions()
{
}

void MacroFunctions::Init(bool initNox)
{
	if (initNox)
	{
		noxObj				.Init("nox.png"						, 125	, 250	, -1				, 1920					);
	}
	else
	{
		energyBarNotEmpty	.Init("energy_not_empty.png"		, 100	, 200	, SearchObj::noxX1							);
		dungObj				.Init("earth_shrine_exit.png"		, 600	, 800	, -1				, SearchObj::noxWidth	);
		nextObj				.Init("next.png"					, 850	, 200												);
		scrollerObj			.Init("scroll.png"					, 300	, 350	, SearchObj::noxX2							);
		noCompanion			.Init("no_companion.png"			, 900	, 200												);
		depart				.Init("depart.png"					, 850	, 200												);
		limit				.Init("limit.png"					, 750	, 300	, -1				, SearchObj::noxWidth	);
		limitx				.Init("limit.png"					, 650	, 100												);
		repeat				.Init("repeat.png"					, 950	, 200												);
		repeatDisabled		.Init("repeat_disabled.png"			, 950	, 200												);
		resultsGil			.Init("results_gil.png"				, 400	, 200												);
		resultsExp			.Init("results_exp.png"				, 150	, 200												);
		resultsItems		.Init("results_items.png"			, 150	, 200												);
		nextResultsItems	.Init("next_results_items.png"		, 850	, 200												);
		dailyQuestCompleted	.Init("daily_quest_completed.png"	, 250	, 200	, -1				, SearchObj::noxWidth	);
		dailyQuestClose		.Init("daily_quest_close.png"		, 600	, 200	, SearchObj::noxX1							);
		connError			.Init("connection_error.png"		, 500	, 500	, -1				, SearchObj::noxWidth	);
		okButtonConnErr		.Init("ok_button_conn_err.png"		, 550	, 200												);
	}
}

int MacroFunctions::Run()
{
	bool attackStepNeeded = true;
	int times = 100;
	while (times--)
	{
 		for (FunctionName fn : earthShrineSteps)
		{
			if (fn.step == ClickAttackStep && attackStepNeeded == false)
				continue;
			else if (fn.step == ClickRepeatStep && attackStepNeeded == true)
				continue;

			if ((this->*(fn.function))() == 0)
			{
				times = 100;
				int ret = -1;
				switch (fn.step)
				{
				case MacroFunctions::ClickConnectionErrorStep:
					break;
				case MacroFunctions::ClickDailyQuestCompletedStep:
					break;
				case MacroFunctions::ClickDungeon:
					ret = OrderedFastEarthShrineExit(ClickNextStep);
					attackStepNeeded = true;
					break;
				case MacroFunctions::ClickNextStep:
					break;
				case MacroFunctions::ClickNoCompanionStep:
					ret = OrderedFastEarthShrineExit(ClickDepartStep);
					break;
				case MacroFunctions::ClickDepartStep:
					ret = OrderedFastEarthShrineExit(WaitAttackStep);
					break;
				case MacroFunctions::WaitAttackStep:
					break;
				case MacroFunctions::ClickAttackStep:
					attackStepNeeded = false;
					ret = OrderedFastEarthShrineExit(ClickRepeatStep);
					break;
				case MacroFunctions::ClickRepeatStep:
					break;
				case MacroFunctions::WaitResultsStep:
					break;
				case MacroFunctions::ClickResultsGilStep:
					break;
				case MacroFunctions::ClickResultsExpStep:
					break;
				case MacroFunctions::ClickResultsItemsStep:
					break;
				default:
					break;
				}
				int countDown = 15;
				
				while (ret == 0)
				{
					while (countDown--)
					{
						ret = ClickEarthShrine_Exit();
						if (ret == 0)
						{
							ret = OrderedFastEarthShrineExit(ClickNextStep);
							break;
						}
						Sleep(1000);
					}
				}
			}
		}
		Sleep(1000);
	}
	return 0;
}

int MacroFunctions::OrderedFastEarthShrineExit(ActionStepType step)
{
	int currentStep = step;
	while (currentStep != StopStep)
	{
		switch (currentStep++)
		{
		case MacroFunctions::ClickConnectionErrorStep:
			break;
		case MacroFunctions::ClickDailyQuestCompletedStep:
			break;
		case MacroFunctions::ClickDungeon:
			break;
		case MacroFunctions::ClickNextStep:
			if (CLickNext() < 0) 
				return -1;
			break;
		case MacroFunctions::ClickNoCompanionStep:
			if (ClickNoCompanion() < 0) 
				return -1;
			break;
		case MacroFunctions::ClickDepartStep:
			if (ClickDepart() < 0) 
				return -1;
			break;
		case MacroFunctions::WaitAttackStep:
			if (WaitAttack(15) < 0) 
				return -1;
			break;
		case MacroFunctions::ClickAttackStep:
			if (ClickAttack() < 0) 
				return -1;
			break;
		case MacroFunctions::ClickRepeatStep:
			while (ClickRepeat() == 0) Sleep(1000);
			break;
		case MacroFunctions::WaitResultsStep:
			if (WaitResults(15) < 0) 
				return -1;
			break;
		case MacroFunctions::ClickResultsGilStep:
			if (ClickResultsGil() < 0) 
				return -1;
			break;
		case MacroFunctions::ClickResultsExpStep:
			if (ClicResultsExp() < 0) 
				return -1;
			break;
		case MacroFunctions::ClickResultsItemsStep:
			if (ClicResultsItems() < 0) 
				return -1;
			break;
		case MacroFunctions::StopStep:
			break;
		default:
			return -1;
			break;
		}
	}
	return 0;
}

int MacroFunctions::IsNoxPresent()
{
	return noxObj.Search(true);
}

int MacroFunctions::HasEnergy()
{
	return energyBarNotEmpty.Search();
}

int MacroFunctions::ClickConnectionError()
{
	if (connError.Search() == 0 && okButtonConnErr.Search() == 0 && okButtonConnErr.Action() == 0)
	{
		Sleep(3000);
		return 0;
	}
	return -1;
}

int MacroFunctions::ClickDailyQuestCompleted()
{
	if (dailyQuestCompleted.Search() == 0 && dailyQuestClose.Search() == 0 && dailyQuestClose.Action() == 0)
	{
		Sleep(1000);
		return 0;
	}
	return -1;
}

int MacroFunctions::ClickEarthShrine_Exit()
{
	if (dungObj.Search() == 0)
	{
		if (HasEnergy() < 0)
		{
			Sleep(300 * 1000); // 5 minutes
		}
		if (dungObj.Action() == 0);
		{
			Sleep(1000);
			return 0;
		}
	}
	return -1;
}

int MacroFunctions::WaitNext(int howLong)
{
	while (howLong >= 0)
	{
		if (nextObj.Search() == 0) return 0;
		howLong--;
		if (ClickConnectionError() == 0)
		{
			return WaitNext(10);
		}
		Sleep(1000);
	}
	return -1;
}

int MacroFunctions::CLickNext()
{
	if (nextObj.Search() == 0 && nextObj.Action() == 0)
	{
		Sleep(1000);
		return 0;
	}
	return -1;
}

int MacroFunctions::ClickNoCompanion()
{
	if (scrollerObj.Search() == 0 && scrollerObj.Action() == 0) {
		Sleep(500);
		if (noCompanion.Search() == 0 && noCompanion.Action() == 0)
		{
			Sleep(1000);
			return 0;
		}
	}
	return -1;
}

int MacroFunctions::ClickDepart()
{
	if (depart.Search() == 0 && depart.Action() == 0)
	{
		Sleep(3000);
		return 0;
	}
	return -1;
}

int MacroFunctions::WaitAttack(int howLong)
{
	while (howLong >= 0)
	{
		if (limit.Search() == 0) return 0;
		howLong--;
		if (ClickConnectionError() == 0)
		{
			return WaitAttack(10);
		}
		Sleep(1000);
	}
	return -1;
}

int MacroFunctions::ClickAttack()
{
	if (limit.Search() == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			limitx.searchAreaMidX = (SearchObj::noxX2 - SearchObj::noxX1) / 2;
			limitx.searchAreaMidY += i * 100;
			if (limitx.Search() == 0)
				limitx.Action();
			limitx.searchAreaMidX = SearchObj::noxX2;
			if (limitx.Search() == 0)
				limitx.Action();
		}
		return 0;
	}
	return -1;
}

int MacroFunctions::ClickRepeat()
{
	int countDown = 20;
	while (countDown >= 0)
	{
		if (repeat.Search() == 0 && repeat.Action() == 0)
		{
			return 0;
		}
		if (repeatDisabled.Search() < 0) 
			return -1;
		countDown--;
		Sleep(1000);
	}
	return -1;
}

int MacroFunctions::WaitResults(int howLong)
{
	while (howLong >= 0)
	{
		if (resultsGil.Search() == 0) return 0;
		howLong--;
		if (ClickConnectionError() == 0)
		{
			return WaitResults(10);
		}
		Sleep(1000);
	}
	return -1;
}

int MacroFunctions::ClickResultsGil()
{
	if (resultsGil.Search() == 0)
	{
		if (resultsGil.Action() == 0) Sleep(500); // gil
		if (resultsGil.Action() == 0) Sleep(500); // unit exp
		if (resultsGil.Action() == 0) Sleep(500); // rank exp
		if (nextObj.Search() == 0 && nextObj.Action() == 0)
		{
			Sleep(1000);
			return 0;
		}
	}
	return -1;
}

int MacroFunctions::ClicResultsExp()
{
	if (resultsExp.Search() == 0 && resultsExp.Action() == 0)
	{
		Sleep(1000);
		return 0;
	}
	return -1;
}

int MacroFunctions::ClicResultsItems()
{
	if (resultsItems.Search() == 0 && resultsItems.Action() == 0)
	{
		Sleep(2000);
	}
	if (nextResultsItems.Search() == 0 && nextResultsItems.Action() == 0)
	{
		Sleep(3000);
		return 0;
	}
	return -1;
}