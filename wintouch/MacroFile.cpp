#include "MacroFile.h"
#include <fstream>
#include <map>
#include "Log.h"
#include "MacroFunctions.h"

using namespace std;

// Register New macros that can be used in macros.dat file here.
int MacroFile::InitMacroNames()
{
	MacroNames["ClickEarthShrine_Exit"			] = std::pair<int, macroFuncType>(ClickEarthShrine_Exit	, MacroFunctions::ClickEarthShrine_Exit	);
	MacroNames["ClickNextStep"					] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickNoCompanionStep"			] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickDepartStep"				] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["WaitAttackStep"					] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickAttackStep"				] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickRepeatStep"				] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["WaitResultsStep"				] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickResultsGilStep"			] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickResultsExpStep"			] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickResultsItemsStep"			] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickConnectionErrorStep"		] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	MacroNames["ClickDailyQuestCompletedStep"	] = std::pair<int, macroFuncType>(ClickDungeon			, MacroFunctions::IsNoxPresent			);
	return 0;
}

int MacroFile::LoadMacroFile()
{
	string fileName("macros.dat");
	LOG("Reading file: " + fileName);
	ifstream f(fileName);
	InitMacroNames();
	lineNo = 0;
	int ret = 0;

	if (f.is_open())
	{
		macroStepDB.clear();
		string line, dungName, stepName, nexStepName;

		while (getline(f, line))
		{
			lineNo++;
			if(line.empty()) continue;
			if (line[0] == '[')
			{
				if (line == "[DUNG_NAME]")
				{
					int retflag;
					ReadDungName(f, line, retflag);
					if (retflag == 2) {ret = -1; break; }
					if (retflag == 3) continue;
				}
				else if (line == "[SEQUENTIAL_STEPS]")
				{
					int retflag;
					ReadSequentialSteps(f, line, retflag);
					if (retflag == 2) { ret = -1; break; }
				}
				else if (line == "[UNIQUE_STEPS]")
				{
					int retflag;
					ReadUniqueSteps(f, line, retflag);
					if (retflag == 2) { ret = -1; break; }
				}
				else if (line == "[COMMON_STEPS]")
				{
					int retflag;
					ReadCommonSteps(f, line, retflag);
					if (retflag == 2) { ret = -1; break; }
				}
				else
				{
					LOG("Unexpected line: " + line + "   ...skipping");
				}
			}
			else
			{
				LOG("Unexpected line: " + line + "   ...skipping");
			}
		}

		f.close();
	}
	else
	{
		LOG("Can't open " + fileName);
	}

	LOG("Finished reading: " + fileName);

	return ret;
}

int MacroFile::FindDung(std::string dungName)
{
	int ret = -1;
	if (macroStepDB.empty())
	{
		LOG("macroStepDB is empty");
	}
	else
	{
		int i = 0;
		for (MacroSteps dung : macroStepDB)
		{
			if (dung.dungName == dungName)
			{
				ret = i;
				break;
			}
			++i;
		}
	}
	return ret;
}

void MacroFile::ReadCommonSteps(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;

	if (macroStepDB.empty())
	{
		MacroSteps mSteps = MacroSteps();
		mSteps.dungName = ALL_DUNG_NAME;
		macroStepDB.push_back(mSteps);
	}

	int allLocation = -1;
	int i = 0;
	for (MacroSteps dung : macroStepDB)
	{
		if (dung.dungName == ALL_DUNG_NAME)
		{
			allLocation = i;
			break;
		}
		++i;
	}
	if (allLocation < 0)
	{
		LOG("Coudn't create and doesn't exist dung for Common steps");
		{ retflag = 2; return; };
	}

	while (getline(f, line))
	{
		lineNo++;
		if (line.empty())
		{
			break;
		}
		else if (line[0] == '[')
		{
			LOG("Empty line expected before " + line);
			{ retflag = 2; return; };
		}
		else if (line.substr(0, 2) == "1_")
		{
			if (InsertMacroStep(macroStepDB.at(allLocation).commonSteps, line) < 0)
			{
				LOG("Macro step insertion failed, line: " + line);
				{ retflag = 2; return; };
			}
		}
		else
		{
			LOG("Unexpected [COMMON_STEPS] line: " + line + "   ...skipping");
		}
	}
	if (macroStepDB.at(allLocation).commonSteps.empty())
	{
		LOG("[COMMON_STEPS] is empty" + line);
	}
}

void MacroFile::ReadUniqueSteps(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;
	if (macroStepDB.empty())
	{
		LOG("[UNIQUE_STEPS] found before first [DUNG_NAME]");
		{ retflag = 2; return; };
	}
	if (macroStepDB.at(macroStepDB.size() - 1).sequentialSteps.empty())
	{
		LOG("[UNIQUE_STEPS] found before first [SEQUENTIAL_STEPS]");
		{ retflag = 2; return; };
	}
	bool firstFound = false;
	while (getline(f, line))
	{
		lineNo++;
		if (line.size() < 2)
		{
			break;
		}
		else if (line[0] == '[')
		{
			LOG("Empty line expected before " + line);
			{ retflag = 2; return; };
		}
		else if (line.substr(0, 2) == "1_")
		{
			if (line.size() == 2)
			{
				LOG("Line starting with '1_' should contain a name");
				{ retflag = 2; return; };
			}
			if (InsertMacroStep(macroStepDB.at(macroStepDB.size() - 1).uniqueSteps, line) < 0)
			{
				LOG("Macro step insertion failed, line: " + line);
				{ retflag = 2; return; };
			}
			else
			{
				firstFound = true;
			}
		}
		else if (line.substr(0, 2) == "2_")
		{
			if (line.size() == 2)
			{
				continue;
			}
			if (FindStep(macroStepDB.at(macroStepDB.size() - 1).sequentialSteps, line.substr(2)) < 0)
			{
				LOG("Next Step not found in [SEQUENTIAL_STEPS], line: " + line);
				{ retflag = 2; return; };
			}
			if (firstFound == false)
			{
				LOG("Next Step should be AFTER current step, line: " + line);
				{ retflag = 2; return; };
			}
			if (InsertMacroStep(macroStepDB.at(macroStepDB.size() - 1).uniqueSteps, line) < 0)
			{
				LOG("Macro step insertion failed, line: " + line);
				{ retflag = 2; return; };
			}
			else
			{
				firstFound = false;
			}
		}
		else
		{
			LOG("Unexpected [SEQUENTIAL_STEPS] line: " + line);
		}
	}
	if (macroStepDB.at(macroStepDB.size() - 1).sequentialSteps.empty())
	{
		LOG("[UNIQUE_STEPS] is empty" + line);
		{ retflag = 2; return; };
	}
}

void MacroFile::ReadSequentialSteps(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;
	if (macroStepDB.empty())
	{
		LOG("[SEQUENTIAL_STEPS] found before first [DUNG_NAME]");
		{ retflag = 2; return; };
	}

	while (getline(f, line))
	{
		lineNo++;
		if (line.size() < 3)
		{
			break;
		}
		else if (line[0] == '[')
		{
			LOG("Empty line expected before " + line);
			{ retflag = 2; return; };
		}
		else if (line.substr(0, 2) == "1_")
		{
			if (InsertMacroStep(macroStepDB.at(macroStepDB.size() - 1).sequentialSteps, line) < 0)
			{
				LOG("Macro step insertion failed, line: " + line);
				{ retflag = 2; return; };
			}
		}
		else
		{
			LOG("Unexpected [SEQUENTIAL_STEPS] line: " + line + "   ...skipping");
		}
	}
	if (macroStepDB.at(macroStepDB.size() - 1).sequentialSteps.empty())
	{
		LOG("[SEQUENTIAL_STEPS] is empty" + line);
		{ retflag = 2; return; };
	}
}

void MacroFile::ReadDungName(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;
	MacroSteps mSteps = MacroSteps();
	macroStepDB.push_back(mSteps);
	if (getline(f, line))
	{
		lineNo++;
		if (line.empty())
		{
			LOG("Line after [DUNG_NAME] can't be empty!");
			{ retflag = 2; return; };
		}
		else if (line[0] == '[')
		{
			LOG("Line after [DUNG_NAME] can't start with '[' !");
			{ retflag = 2; return; };
		}
		else
		{
			macroStepDB.at(macroStepDB.size() - 1).dungName = line;
			{ retflag = 3; return; };
		}
	}
}

int MacroFile::InsertMacroStep(vector<MacroStep>& mSteps, std::string line)
{
	int ret = -1, stepNo = -1;
	MacroStep mStep = MacroStep();

	if (line.substr(0,2) == "1_") stepNo = 1;
	else if (line.substr(0,2) == "2_") stepNo = 2;
	else { LOG("step Name should start with '1_' or '2_'");}


	if (stepNo > 0)
	{
		string stepName = line.substr(2);
		int stepId = -1;
		macroFuncType function;
		stepId = GetMacroStepId(stepName);
		function = GetMacroStepFunction(stepName);

		if (stepId < 0 || function == nullptr)
		{
			LOG("Couldn't find a step with a name " + stepName);
			ret = -1;
		}
		else
		{
			ret = 0;
		}

		if (stepNo == 1)
		{
			mStep.name = stepId;
			mStep.function = function;
			mStep.nextStepName = -1;
		}
		else if (stepNo = 2)
		{
			mStep.nextStepName = stepId;
		}
	}
	if (ret == 0)
	{
		if (stepNo == 1)
			mSteps.push_back(mStep);
		else if (mSteps.empty())
		{
			LOG("Before entering Next step name, current step should be defined: " + line);
			ret = -1;
		}
		else
			mSteps.at(mSteps.size() - 1).nextStepName = mStep.nextStepName;
	}
	return ret;
}

int MacroFile::GetMacroStepId(std::string stepName)
{
	int ret = -1;
	if (MacroNames.count(stepName) > 0)
		ret = MacroNames[stepName].first;
	return ret;
}

macroFuncType MacroFile::GetMacroStepFunction(std::string stepName)
{
	macroFuncType ret = nullptr;
	if (MacroNames.count(stepName) > 0)
		ret = MacroNames[stepName].second;
	return ret;
}

int MacroFile::FindStep(std::vector<MacroStep>& mSteps, std::string stepName)
{
	int ret = -1;
	int stepId = GetMacroStepId(stepName);
	if (stepId < 0)
	{
		LOG("Couldn't find a step with a name " + stepName);
		ret = -1;
	}
	else
	{
		ret = FindStep(mSteps, stepId);
	}
	
	return ret;
}

int MacroFile::FindStep(std::vector<MacroStep>& mSteps, int stepName)
{
	int ret = -1;
	if (stepName < 0)
	{
		LOG("Couldn't find a step with negative id");
	}
	else
	{
		int i = 0;
		for (MacroStep item : mSteps)
		{
			if (item.name == stepName)
			{
				ret = i;
				break;
			}
			++i;
		}
	}

	return ret;
}

std::vector<MacroSteps>MacroFile::macroStepDB = std::vector<MacroSteps>();
std::map<std::string, std::pair<int, macroFuncType> >MacroFile::MacroNames = std::map<std::string, std::pair<int, macroFuncType> >();
int MacroFile::lineNo = 0;
const std::string MacroFile::ALL_DUNG_NAME = "ALL";