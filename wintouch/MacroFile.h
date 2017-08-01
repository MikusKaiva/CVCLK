#pragma once
#include <string>
#include <vector>
#include <map>
#include "MacroFunctions.h"

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

struct MacroStep
{
	int name;
	int (* function)(void);
	int nextStepName;
};

struct MacroSteps
{
	std::string dungName;
	std::vector<MacroStep> sequentialSteps;
	std::vector<MacroStep> uniqueSteps;
	std::vector<MacroStep> commonSteps;
};

static class MacroFile
{
public:
	MacroFile()
	{
	}

	~MacroFile()
	{
	}
	static int LoadMacroFile();
	static std::vector<MacroSteps> MacroStepDB;

private:
	static void ReadCommonSteps(std::ifstream &f, std::string &line, int &retflag);
	static void ReadUniqueSteps(std::ifstream &f, std::string &line, int &retflag);
	static void ReadSequentialSteps(std::ifstream &f, std::string &line, int &retflag);
	static void ReadDungName(std::ifstream &f, std::string &line, int &retflag);
	static int InsertMacroStep(std::vector<MacroStep>& mSteps, std::string line);
	static int InitMacroNames();
	static int GetMacroStepId(std::string stepName);
	static int(*GetMacroStepFunction(std::string stepName))(void);
	static bool MacroStepExists(std::vector<MacroStep>& mSteps, std::string stepName);
	static std::map<std::string, std::pair<int, int(*)(void)> > MacroNames;
	static int lineNo;
	static const std::string ALL_DUNG_NAME;
};



