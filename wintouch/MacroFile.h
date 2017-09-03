#pragma once
#include <string>
#include <vector>
#include <map>
#include "MacroFunctions.h"

typedef int(*macroFuncType)(void);

enum ActionStepType
{
	ClickConnectionErrorStep
	, ClickDailyQuestCompletedStep
	, ClickEarthShrine_Exit
	, ClickMissionsStep
	, ClickNoCompanionStep
	, ClickDepartStep
	, WaitAttackStep
	, ClickAttackStep
	, WaitResultsStep
	, ClickResultsGilStep
	, ClickResultsExpStep
	, ClickResultsItemsStep
	, StopStep
};

struct MacroStep
{
	int name;
	macroFuncType function;
	int nextStepName;
};

struct MacroSteps
{
	std::string dungName;
	std::vector<MacroStep> sequentialSteps;
	std::vector<MacroStep> uniqueSteps;
	std::vector<MacroStep> commonSteps;
};

class MacroFile
{
public:
	static int LoadMacroFile();
	static std::vector<MacroSteps> macroStepDB;
	static int FindDung(std::string dungName);
	static int FindStep(std::vector<MacroStep>& mSteps, int stepName);
	static const std::string ALL_DUNG_NAME;

private:
	static void ReadCommonSteps(std::ifstream &f, std::string &line, int &retflag);
	static void ReadUniqueSteps(std::ifstream &f, std::string &line, int &retflag);
	static void ReadSequentialSteps(std::ifstream &f, std::string &line, int &retflag);
	static void ReadDungName(std::ifstream &f, std::string &line, int &retflag);
	static int InsertMacroStep(std::vector<MacroStep>& mSteps, std::string line);
	static int InitMacroNames();
	static int FindStep(std::vector<MacroStep>& mSteps, std::string stepName);
	static int GetMacroStepId(std::string stepName);
	static macroFuncType GetMacroStepFunction(std::string stepName);
	static std::map<std::string, std::pair<int, macroFuncType> > MacroNames;
	static int lineNo;
};



