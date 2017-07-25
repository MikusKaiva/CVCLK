#pragma once
#include <vector>
#include "SearchObj.h"

class MacroFunctions
{
public:
	enum ActionStepType
	{
		  ClickConnectionErrorStep
		, ClickDailyQuestCompletedStep
		, ClickDungeon
		, ClickNextStep
		, ClickNoCompanionStep
		, ClickDepartStep
		, WaitAttackStep
		, ClickAttackStep
		, ClickRepeatStep
		, WaitResultsStep
		, ClickResultsGilStep
		, ClickResultsExpStep
		, ClickResultsItemsStep
		, StopStep
	};

	struct FunctionName
	{
		FunctionName(ActionStepType step, int(MacroFunctions::* function)(void)) : step(step), function(function)
		{
		};
		ActionStepType step;
		int (MacroFunctions::* function)(void);
	};

	MacroFunctions();
	~MacroFunctions();
	void Init(bool initNox = false);
	int Run();

	int OrderedFastEarthShrineExit(ActionStepType step);

	int IsNoxPresent();
	int HasEnergy();
	int ClickConnectionError();
	int ClickDailyQuestCompleted();

	int ClickEarthShrine_Exit();
	int WaitNext(int howLong);
	int CLickNext();
	int ClickNoCompanion();
	int ClickDepart();
	int WaitAttack(int howLong);
	int ClickAttack();
	int ClickRepeat();
	int WaitResults(int howLong);
	int ClickResultsGil();
	int ClicResultsExp();
	int ClicResultsItems();

private:
	std::vector<FunctionName> earthShrineSteps;

	SearchObj noxObj; // TODO: Maybe static?
	SearchObj energyBarNotEmpty;
	SearchObj dungObj;
	SearchObj nextObj;
	SearchSlider scrollerObj;
	SearchObj noCompanion;
	SearchObj depart;
	SearchObj limit;
	SearchObj limitx;
	SearchObj repeat;
	SearchObj repeatDisabled;
	SearchObj resultsGil;
	SearchObj resultsExp;
	SearchObj resultsItems;
	SearchObj nextResultsItems;
	SearchObj dailyQuestCompleted;
	SearchObj dailyQuestClose;
	SearchObj connError;
	SearchObj okButtonConnErr;
};

