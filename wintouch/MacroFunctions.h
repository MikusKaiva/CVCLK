#pragma once
#include <string>
#include <vector>

typedef int(*macroFuncType)(void);

struct MacroStep;
public class MacroFunctions
{
public:
	static int Run(std::string dungName);
	static int RunSequential(std::vector<MacroStep>& sequentialSteps, int stepName);

	static int isPaused;
	static int isStopped;

private:
	static int ProcessPauseAndStop();
	static int MacroFuncCaller(macroFuncType f);

public:
	static int IsNoxPresent();
	static int Wait(int miliSeconds);
	static int ClickEarthShrine_Exit();
	static int ClickConnectionError();
	static int ClickDailyQuestCompletedStep();
	static int ClickMissions();
	static int ClickNoCompanion();
	static int ClickDepart();
	static int WaitAttack();
	static int ClickAttack();
};



