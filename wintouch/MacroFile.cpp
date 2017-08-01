#include "MacroFile.h"
#include <fstream>
#include <map>
#include "Log.h"
#include "MacroFunctions.h"

using namespace std;

// Register New macros that can be used in macros.dat file here.
int MacroFile::InitMacroNames()
{
	MacroNames["ClickDungeon"					] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickNextStep"					] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickNoCompanionStep"			] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickDepartStep"				] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["WaitAttackStep"					] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickAttackStep"				] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickRepeatStep"				] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["WaitResultsStep"				] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickResultsGilStep"			] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickResultsExpStep"			] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickResultsItemsStep"			] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickConnectionErrorStep"		] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	MacroNames["ClickDailyQuestCompletedStep"	] = std::pair<int, int(*)(void)>(ClickDungeon, MacroFunctions::IsNoxPresent);
	return 0;
}

int MacroFile::LoadMacroFile()
{
	string fileName("macros.dat");
	LOG("Reading file: " + fileName);
	ifstream f(fileName);
	InitMacroNames();
	lineNo = 0;

	if (f.is_open())
	{
		MacroStepDB.clear();
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
					if (retflag == 2) break;
					if (retflag == 3) continue;
				}
				else if (line == "[SEQUENTIAL_STEPS]")
				{
					int retflag;
					ReadSequentialSteps(f, line, retflag);
					if (retflag == 2) break;
				}
				else if (line == "[UNIQUE_STEPS]")
				{
					int retflag;
					ReadUniqueSteps(f, line, retflag);
					if (retflag == 2) break;
				}
				else if (line == "[COMMON_STEPS]")
				{
					int retflag;
					ReadCommonSteps(f, line, retflag);
					if (retflag == 2) break;
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

	return 0;
}

void MacroFile::ReadCommonSteps(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;

	if (MacroStepDB.empty())
	{
		MacroSteps mSteps = MacroSteps();
		mSteps.dungName = ALL_DUNG_NAME;
		MacroStepDB.push_back(mSteps);
	}

	int allLocation = -1;
	int i = 0;
	for (MacroSteps dung : MacroStepDB)
	{
		if (dung.dungName == ALL_DUNG_NAME)
			allLocation = i;
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
			if (InsertMacroStep(MacroStepDB.at(allLocation).commonSteps, line) < 0)
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
	if (MacroStepDB.at(allLocation).commonSteps.empty())
	{
		LOG("[COMMON_STEPS] is empty" + line);
	}
}

void MacroFile::ReadUniqueSteps(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;
	if (MacroStepDB.empty())
	{
		LOG("[UNIQUE_STEPS] found before first [DUNG_NAME]");
		{ retflag = 2; return; };
	}
	if (MacroStepDB.at(MacroStepDB.size() - 1).sequentialSteps.empty())
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
			if (InsertMacroStep(MacroStepDB.at(MacroStepDB.size() - 1).uniqueSteps, line) < 0)
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
			if (!MacroStepExists(MacroStepDB.at(MacroStepDB.size() - 1).sequentialSteps, line.substr(2)))
			{
				LOG("Next Step not found in [SEQUENTIAL_STEPS], line: " + line);
				{ retflag = 2; return; };
			}
			if (firstFound == false)
			{
				LOG("Next Step should be AFTER current step, line: " + line);
				{ retflag = 2; return; };
			}
			if (InsertMacroStep(MacroStepDB.at(MacroStepDB.size() - 1).uniqueSteps, line) < 0)
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
	if (MacroStepDB.at(MacroStepDB.size() - 1).sequentialSteps.empty())
	{
		LOG("[UNIQUE_STEPS] is empty" + line);
		{ retflag = 2; return; };
	}
}

void MacroFile::ReadSequentialSteps(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;
	if (MacroStepDB.empty())
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
			if (InsertMacroStep(MacroStepDB.at(MacroStepDB.size() - 1).sequentialSteps, line) < 0)
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
	if (MacroStepDB.at(MacroStepDB.size() - 1).sequentialSteps.empty())
	{
		LOG("[SEQUENTIAL_STEPS] is empty" + line);
		{ retflag = 2; return; };
	}
}

void MacroFile::ReadDungName(std::ifstream &f, std::string &line, int &retflag)
{
	retflag = 1;
	MacroSteps mSteps = MacroSteps();
	MacroStepDB.push_back(mSteps);
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
			MacroStepDB.at(MacroStepDB.size() - 1).dungName = line;
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
		int(*function)(void);
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

int(*MacroFile::GetMacroStepFunction(std::string stepName))(void)
{
	int(*ret)(void) = nullptr;
	if (MacroNames.count(stepName) > 0)
		ret = MacroNames[stepName].second;
	return ret;
}

bool MacroFile::MacroStepExists(std::vector<MacroStep>& mSteps, std::string stepName)
{
	bool ret = false;
	int stepId = GetMacroStepId(stepName);
	if (stepId < 0)
	{
		LOG("Couldn't find a step with a name " + stepName);
		ret = false;
	}
	else
	{
		for (MacroStep item : mSteps)
		{
			if (item.name == stepId)
			{
				ret = true;
				break;
			}
		}
	}
	
	return ret;
}

std::vector<MacroSteps>MacroFile::MacroStepDB = std::vector<MacroSteps>();
std::map<std::string, std::pair<int, int(*)(void)> >MacroFile::MacroNames = std::map<std::string, std::pair<int, int(*)(void)> >();
int MacroFile::lineNo = 0;
const std::string MacroFile::ALL_DUNG_NAME = "ALL";